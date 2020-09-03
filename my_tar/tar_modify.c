#include "task.h"
#include "tar.h"

int tar_append(int archive_fd, ItemName *item_name, char *cd_path)
{
    int res;
    Item *item;
    lseek(archive_fd, -FOOTER_SIZE, SEEK_END);
    while (item_name != NULL)
    {
        item = init_item(item_name->value, cd_path);
        res = archive_item(archive_fd, item);
        free(item);
        if (res < 0) return FAILURE;
        item_name = item_name->next;
    }
    return write_footer(archive_fd);
}

int tar_update(int archive_fd, ItemName *item_names, char *cd_path)
{
    Item *item;
    ItemHeader header;
    int res, skip_size;
    ItemName *item_name;
    struct stat status = {};
    while ((res = read_header(archive_fd, &header)) > 0)
    {
        item_name = item_names;
        while (item_name != NULL)
        {
            if (strcmp(item_name->value, header.name) == 0)
            {
                item = init_item(item_name->value, cd_path);
                if (lstat(item->real_path, &status) < 0)
                {
                    ITEM_STAT_ERROR;
                    return FAILURE;
                }
                if (status.st_mtime <= my_strtol(header.mtime, 8))
                {
                    item_name->value = "";
                }
                reset(&status, sizeof status);
                free_item(item);
            }
            item_name = item_name->next;
        }
        if (header.typeflag == REGTYPE || header.typeflag == AREGTYPE)
        {
            skip_size = count_blocks(my_strtol(header.size, 8)) * BLOCK_SIZE;
            lseek(archive_fd, skip_size, SEEK_CUR);
        }
    }
    lseek(archive_fd, -FOOTER_SIZE, SEEK_END);
    item_name = item_names;
    while (item_name != NULL)
    {
        if (strlen(item_name->value) > 0)
        {
            item = init_item(item_name->value, cd_path);
            res = archive_item(archive_fd, item);
            free_item(item);
            if (res < 0) return FAILURE;
        }
        item_name = item_name->next;
    }
    return write_footer(archive_fd);
}