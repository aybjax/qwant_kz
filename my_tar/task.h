#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SUCCESS 0
#define FAILURE -1

#define MALLOC_ERROR fprintf(stderr, "Failed to allocate memory\n");
#define TAR_FILE_ERROR fprintf(stderr, "Failed to open/create archive\n");
#define DIR_CHANGE_ERROR fprintf(stderr, "Failed to change directory\n");

typedef enum
{
    false,
    true
} bool;

enum TaskMode
{
    CREATE = 'c',
    APPEND = 'r',
    LIST = 't',
    UPDATE = 'u',
    EXTRACT = 'x'
};

struct node
{
    char *value;
    struct node *next;
};

typedef struct node ItemName;

typedef struct
{
    enum TaskMode mode;

    bool file_mode;
    char *file_path;
    int file_fd;

    bool cd_mode;
    char *dir_path;

    ItemName *items;
} Task;

/* Common */
void my_memset(void *, int, size_t);
void reset(void *, size_t);
long my_strtol(const char *, int);
void itoa_octal(long, char *, size_t);
bool is_dir(char *);

/* Linked list operations */
struct node *add_node(struct node *, char *);
void free_list(struct node *);

/* Task operations */
Task *task_init(void);
int task_prepare(Task *);
int task_run(Task *);
void task_end(Task *);