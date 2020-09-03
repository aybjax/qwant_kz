#include "task.h"
#include "tar.h"

int tar_create(int archive_fd, ItemName *item_name, char *cd_path)
{
    int res;
    Item *item;
    while (item_name != NULL)
    {
        item = init_item(item_name->value, cd_path);
        res = archive_item(archive_fd, item);
        free_item(item);
        if (res < 0) return FAILURE;
        item_name = item_name->next;
    }
    return write_footer(archive_fd);
}