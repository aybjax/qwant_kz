#include "task.h"
#include "tar.h"

/* Computations */

int checksum(void *buffer, size_t size)
{
    int sum = 0;
    for (size_t i = 0; i < size; i++) sum += ((char *)buffer)[i];
    return sum;
}

int count_blocks(size_t size)
{
    return size ? size / BLOCK_SIZE + 1 : 0;
}

/* Read tar functions */

bool is_header(ItemHeader *header)
{
    int chksum = my_strtol(header->chksum, 8);
    my_memset(header->chksum, ' ', sizeof header->chksum);
    return chksum == checksum(header, sizeof *header);
}

int read_header(int archive_fd, ItemHeader *header)
{
    int size;
    reset(header, sizeof *header);
    if ((size = read(archive_fd, header, BLOCK_SIZE)) > 0)
    {
        if (size < BLOCK_SIZE)
        {
            TRUNCATED_ERROR;
            return FAILURE;
        }
        if (header->name[0] == 0 &&
            checksum(header, sizeof *header) == 0)  //  End of archive
            return 0;
        if (!is_header(header))
        {
            DAMAGED_ERROR;
            return FAILURE;
        }
    }
    return size;
}

/* Write tar functions */

Item *init_item(char *name, char *cd_path)
{
    Item *item = malloc(sizeof(Item));
    if (item != NULL)
    {
        item->name = strdup(name);
        if (cd_path != NULL)
        {
            item->cd_path = strdup(cd_path);
            if ((item->real_path = malloc(1024)) == NULL) return NULL;
            build_path(item->real_path, cd_path, name);
        }
        else
        {
            item->cd_path = NULL;
            item->real_path = strdup(item->name);
        }
    }
    return item;
}

void free_item(Item *item)
{
    free(item->name);
    free(item->cd_path);
    free(item->real_path);
    free(item);
}

char *build_path(char *dest, const char *path_1, const char *path_2)
{
    size_t len = strlen(path_1);
    strcat(dest, path_1);
    strcat(dest, (path_1[len - 1] != '/') ? "/" : "");
    strcat(dest, path_2);
    return dest;
}

int get_typeflag(mode_t mode)
{
    switch (mode & S_IFMT)
    {
        case S_IFREG:
            return REGTYPE;
        case S_IFDIR:
            return DIRTYPE;
        case S_IFLNK:
            return SYMTYPE;
        default:
            return FAILURE;
    }
}

int write_header(int archive_fd, ItemHeader *header)
{
    if (write(archive_fd, header, BLOCK_SIZE) < 0) return FAILURE;
    return SUCCESS;
}

int write_file_content(int archive_fd, char *file_path)
{
    int fd = open(file_path, O_RDONLY);
    if (fd < 0)
    {
        FILE_OPEN_ERROR;
        return FAILURE;
    }
    char buffer[BLOCK_SIZE] = {};
    while (read(fd, buffer, BLOCK_SIZE) > 0)
    {
        write(archive_fd, buffer, BLOCK_SIZE);
        reset(buffer, sizeof buffer);
    }
    close(fd);
    return SUCCESS;
}

int set_header_name(char *item_name, ItemHeader *header)
{
    char *split_ch;
    size_t pathname_len = strlen(item_name);
    size_t path_len, name_len;
    if (pathname_len <= sizeof header->name)
    {
        strncpy(header->name, item_name, sizeof header->name);
    }
    else
    {
        if ((split_ch = strrchr(item_name, '/')) == NULL) return FAILURE;
        path_len = split_ch - item_name;
        name_len = pathname_len - path_len - 1;
        if (path_len > sizeof header->prefix || name_len > sizeof header->name)
            return FAILURE;
        strncpy(header->name, split_ch + 1, name_len);
        strncpy(header->prefix, item_name, path_len);
    }
    return SUCCESS;
}

int build_header(ItemHeader *header, Item *item)
{
    struct stat status = {};
    struct passwd *pwd;
    struct group *grp;
    if (lstat(item->real_path, &status) < 0)
    {
        ITEM_STAT_ERROR;
        return FAILURE;
    }
    if ((header->typeflag = get_typeflag(status.st_mode)) < 0)
    {
        UNSUPPORTED_TYPE_ERROR;
        return FAILURE;
    }
    if (header->typeflag == SYMTYPE)
    {
        if (readlink(item->real_path, header->linkname, sizeof header->linkname) < 0)
        {
            SYM_READ_ERROR;
            return FAILURE;
        }
    }
    if (set_header_name(item->name, header) < 0)
    {
        LONG_PATHNAME_ERROR;
        return FAILURE;
    }
    if ((pwd = getpwuid(status.st_uid)) == NULL ||
        (grp = getgrgid(status.st_gid)) == NULL)
    {
        USER_GROUP_ERROR;
        return FAILURE;
    }

    itoa_octal(status.st_mode & 07777, header->mode, sizeof header->mode);
    itoa_octal(status.st_uid, header->uid, sizeof header->uid);
    itoa_octal(status.st_gid, header->gid, sizeof header->gid);
    itoa_octal(status.st_size, header->size, sizeof header->size);
    itoa_octal(status.st_mtime, header->mtime, sizeof header->mtime);
    strncpy(header->magic, TMAGIC, TMAGLEN);
    strncpy(header->version, TVERSION, TVERSLEN);
    strncpy(header->uname, pwd->pw_name, sizeof header->uname);
    strncpy(header->gname, grp->gr_name, sizeof header->gname);
    my_memset(header->chksum, ' ', sizeof header->chksum);
    itoa_octal(checksum(header, sizeof *header), header->chksum, sizeof header->chksum);

    return SUCCESS;
}

int archive_dir_items(int archive_fd, Item *dir)
{
    int res;
    Item *item;
    DIR *dir_stream;
    struct dirent *entry;
    char item_name[1024] = {};

    if ((dir_stream = opendir(dir->real_path)) == NULL)
    {
        DIR_OPEN_ERROR;
        return FAILURE;
    }
    while ((entry = readdir(dir_stream)) != NULL)
        if (entry->d_name[0] != '.')
        {
            build_path(item_name, dir->name, entry->d_name);
            item = init_item(item_name, dir->cd_path);
            res = archive_item(archive_fd, item);
            reset(item_name, sizeof item_name);
            free(item);
            if (res < 0) return FAILURE;
        }
    return SUCCESS;
}

int archive_item(int archive_fd, Item *item)
{
    int res = 0;
    ItemHeader header = {};
    res += build_header(&header, item);
    res += write_header(archive_fd, &header);
    switch (header.typeflag)
    {
        case REGTYPE:
            res += write_file_content(archive_fd, item->real_path);
            break;
        case DIRTYPE:
            res += archive_dir_items(archive_fd, item);
            break;
    }
    return res;
}

int write_footer(int archive_fd)
{
    char buf[FOOTER_SIZE] = {};
    return write(archive_fd, buf, FOOTER_SIZE);
}