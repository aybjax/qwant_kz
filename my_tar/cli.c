#include "task.h"
#include "cli.h"

int parse_options(char *option, Task *task)
{
    while (*option)
    {
        switch (*option)
        {
            case 'c':
            case 'r':
            case 't':
            case 'u':
            case 'x':
                if (!task->mode)
                {
                    task->mode = *option;
                }
                else
                {
                    TWO_MODES_ERROR(task->mode, *option);
                    return FAILURE;
                }
                break;
            case 'f':
                task->file_mode = true;
                break;
            case 'C':
                task->cd_mode = true;
                break;
            default:
                OPTION_ERROR(*option);
                return FAILURE;
        }
        option++;
    }
    return SUCCESS;
}

int validate_args(Task *task)
{
    if (task->mode == APPEND || task->mode == UPDATE)
    {
        if (!task->file_mode)
        {
            STDOUT_ERROR;
            return FAILURE;
        }
    }
    if (task->file_mode && !task->file_path)
    {
        NO_FILE_ERROR;
        return FAILURE;
    }
    if (task->cd_mode && !task->dir_path)
    {
        NO_DIR_ERROR;
        return FAILURE;
    }
    if (task->mode == CREATE && task->items == NULL)
    {
        NO_ITEMS_ERROR;
        return FAILURE;
    }
    return SUCCESS;
}

int parse_args(int argc, char **argv, Task *task)
{
    char *arg;
    ItemName *items = NULL;
    for (int i = 0; i < argc; i++)
    {
        arg = argv[i];
        if (arg[0] == '-')
        {
            if (parse_options(arg + 1, task) < 0) return FAILURE;
            continue;
        }
        if (task->file_mode && !task->file_path)
        {
            task->file_path = arg;
            continue;
        }
        if (task->cd_mode && !task->dir_path)
        {
            task->dir_path = arg;
            continue;
        }
        if ((items = add_node(items, arg)) == NULL)
        {
            MALLOC_ERROR;
            return FAILURE;
        }
        if (task->items == NULL) task->items = items;
    }
    return validate_args(task);
}

int cli_parse(int argc, char **argv, Task *task)
{
    if (argc < 2)
    {
        NO_MODE_ERROR;
        return FAILURE;
    }
    if (parse_args(--argc, ++argv, task) < 0) return FAILURE;
    return SUCCESS;
}