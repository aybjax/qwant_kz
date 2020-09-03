#include "task.h"
#include "cli.h"

int main(int argc, char *argv[])
{
    int res = 0;
    Task task = {};
    res += cli_parse(argc, argv, &task);
    res += task_prepare(&task);
    res += task_run(&task);
    task_end(&task);
    return -res;
}