#include "task.h"
#include "tar.h"

/* General */

long my_strtol(const char *str, int base)
{
    long res = 0;
    size_t len = strlen(str);
    for (size_t i = 0; i < len && str[i] >= '0' && str[i] < '0' + base; i++)
        res = base * res + (str[i] - '0');
    return res;
}

void my_memset(void *buf, int c, size_t len)
{
    unsigned char *dst = buf;
    for (; len > 0; len--) *dst++ = (unsigned char)c;
    return;
}

void itoa_octal(long num, char *str, size_t len)
{
    char *numbers = "0123456789abcdef";
    my_memset(str, '0', len);
    str[--len] = '\0';
    do
    {
        str[--len] = numbers[num % 8];
    } while ((num /= 8) > 0);
    return;
}

void reset(void *buf, size_t len)
{
    my_memset(buf, 0, len);
    return;
}

bool is_dir(char *name)
{
    struct stat status;
    return stat(name, &status) == 0 && (status.st_mode & S_IFDIR);
}

/* Linked list operations */

struct node *add_node(struct node *last, char *value)
{
    struct node *new = malloc(sizeof(struct node));
    if (new != NULL) new->value = value;
    if (last != NULL) last->next = new;
    return new;
}

void free_list(struct node *head)
{
    struct node *node;
    while (head != NULL)
    {
        node = head;
        head = head->next;
        free(node);
    }
}

/* Task operations */

int task_run(Task *task)
{
    int res = 0;
    switch (task->mode)
    {
        case CREATE:
            res = tar_create(task->file_fd, task->items, task->dir_path);
            break;
        case EXTRACT:
            res = tar_extract(task->file_fd, task->dir_path);
            break;
        case LIST:
            res = tar_list(task->file_fd);
            break;
        case APPEND:
            res = tar_append(task->file_fd, task->items, task->dir_path);
            break;
        case UPDATE:
            res = tar_update(task->file_fd, task->items, task->dir_path);
            break;
    }
    return res;
}

int task_prepare(Task *task)
{
    mode_t default_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    switch (task->mode)
    {
        case CREATE:
            task->file_fd =
                (task->file_mode)
                    ? open(task->file_path, O_CREAT | O_WRONLY | O_TRUNC, 
                        default_mode)
                    : 1;
            break;
        case EXTRACT:
            task->file_fd =
                (task->file_mode) ? open(task->file_path, O_RDONLY) : 0;
            break;
        case APPEND:
        case UPDATE:
            task->file_fd = open(task->file_path, O_RDWR);
            break;
        case LIST:
            task->file_fd = open(task->file_path, O_RDONLY);
            break;
    }
    if (task->file_fd < 0)
    {
        TAR_FILE_ERROR;
        return FAILURE;
    }
    if (task->cd_mode && !is_dir(task->dir_path))
    {
        DIR_CHANGE_ERROR;
        return FAILURE;
    }
    return SUCCESS;
}

void task_end(Task *task)
{
    if (task->file_fd > 2) close(task->file_fd);
    free_list(task->items);
}