#include "task.h"
#include "tar.h"

int create_file(char *name, int archive_fd, int size, mode_t mode)
{
    int fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, mode);
    if (fd < 0)
    {
        FILE_CREATE_ERROR;
        return FAILURE;
    }
    char buffer[BLOCK_SIZE];
    while (size > 0)
    {
        read(archive_fd, buffer, BLOCK_SIZE);
        write(fd, buffer, size < BLOCK_SIZE ? size : BLOCK_SIZE);
        size -= BLOCK_SIZE;
    }
    close(fd);
    return SUCCESS;
}

int create_dir(char *name, mode_t mode)
{
    if (mkdir(name, mode) < 0 && errno != EEXIST)
    {
        DIR_CREATE_ERROR;
        return FAILURE;
    }
    return SUCCESS;
}

int create_sym(char *name, char *link)
{
    if (symlink(link, name) < 0)
    {
        if (errno == EEXIST)
        {
            unlink(name);
            return create_sym(name, link);
        }
        SYM_CREATE_ERROR;
        return FAILURE;
    }
    return SUCCESS;
}

int extract_item(int archive_fd, ItemHeader *header, char *cd_path)
{
    int res;
    char item_name[1024] = {};

    if (cd_path != NULL) build_path(item_name, cd_path, "");

    if (header->prefix[0] != '\0') build_path(item_name, header->prefix, "");

    strcat(item_name, header->name);

    size_t item_size = my_strtol(header->size, 8);
    mode_t item_mode = my_strtol(header->mode, 8);
    time_t item_mtime = my_strtol(header->mtime, 8);

    errno = 0;
    switch (header->typeflag)
    {
        case REGTYPE:
        case AREGTYPE:
            res = create_file(item_name, archive_fd, item_size, item_mode);
            break;
        case DIRTYPE:
            res = create_dir(item_name, item_mode);
            break;
        case SYMTYPE:
            res = create_sym(item_name, header->linkname);
            break;
        default:
            UNSUPPORTED_TYPE_ERROR;
            return FAILURE;
    }
    if (res < 0) return FAILURE;
    struct utimbuf times = {time(NULL), item_mtime};
    return errno == EEXIST ? SUCCESS : utime(item_name, &times);
}

int tar_extract(int archive_fd, char *cd_path)
{
    ItemHeader header;
    int res;
    while ((res = read_header(archive_fd, &header)) > 0)
    {
        if (extract_item(archive_fd, &header, cd_path) < 0)
        {
            ITEM_EXTRACT_ERROR;
            return FAILURE;
        }
    }
    return res;
}

int tar_list(int archive_fd)
{
    ItemHeader header;
    int res, skip_size;
    while ((res = read_header(archive_fd, &header)) > 0)
    {
        printf("%s\n", header.name);
        if (header.typeflag == REGTYPE || header.typeflag == AREGTYPE)
        {
            skip_size = count_blocks(my_strtol(header.size, 8)) * BLOCK_SIZE;
            lseek(archive_fd, skip_size, SEEK_CUR);
        }
    }
    return res;
}