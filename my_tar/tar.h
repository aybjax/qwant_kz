#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <utime.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

#define BLOCK_SIZE 512
#define FOOTER_SIZE BLOCK_SIZE * 2

#define TRUNCATED_ERROR fprintf(stderr, "Truncated tar archive\n");
#define DAMAGED_ERROR fprintf(stderr, "Damaged tar archive\n");
#define ITEM_EXTRACT_ERROR fprintf(stderr, "Failed to extract an item\n");
#define UNSUPPORTED_TYPE_ERROR fprintf(stderr, "Unknown item type\n");

#define ITEM_STAT_ERROR fprintf(stderr, "Failed to stat an item\n");
#define FILE_OPEN_ERROR fprintf(stderr, "Failed to open a file\n");
#define DIR_OPEN_ERROR fprintf(stderr, "Failed to open a directory\n");
#define SYM_READ_ERROR fprintf(stderr, "Failed to read a symlink\n");

#define USER_GROUP_ERROR fprintf(stderr, "Failed to get user/group name\n");
#define LONG_PATHNAME_ERROR fprintf(stderr, "Pathname too long\n");
#define FILE_CREATE_ERROR fprintf(stderr, "Failed to create a file\n");
#define DIR_CREATE_ERROR fprintf(stderr, "Failed to create a directory\n");
#define SYM_CREATE_ERROR fprintf(stderr, "Failed to create a symlink\n");

typedef struct
{
    char *name;
    char *cd_path;
    char *real_path;
} Item;

typedef struct
{
    char name[100];     /*   0 */
    char mode[8];       /* 100 */
    char uid[8];        /* 108 */
    char gid[8];        /* 116 */
    char size[12];      /* 124 */
    char mtime[12];     /* 136 */
    char chksum[8];     /* 148 */
    char typeflag;      /* 156 */
    char linkname[100]; /* 157 */
    char magic[6];      /* 257 */
    char version[2];    /* 263 */
    char uname[32];     /* 265 */
    char gname[32];     /* 297 */
    char devmajor[8];   /* 329 */
    char devminor[8];   /* 337 */
    char prefix[155];   /* 345 */
    char padding[12];   /* 500 */
} ItemHeader;

#define TMAGIC "ustar" /* ustar and a null */
#define TMAGLEN 6
#define TVERSION "00" /* 00 and no null */
#define TVERSLEN 2

/* Values used in typeflag field.  */
#define REGTYPE '0'   /* regular file */
#define AREGTYPE '\0' /* regular file */
#define SYMTYPE '2'   /* reserved */
#define DIRTYPE '5'   /* directory */

/* Computations */
int checksum(void *, size_t);
int count_blocks(size_t);

/* Read tar functions */
int read_header(int, ItemHeader *);
bool is_header(ItemHeader *); //maybe extract_item?

/* Write tar functions */
Item *init_item(char *, char *);
void free_item(Item *);
char *build_path(char *, const char *, const char *);
int build_header(ItemHeader *, Item *);
int archive_item(int, Item *);
int write_footer(int);

/* Tar operations */
int tar_create(int, ItemName *, char *);
int tar_append(int, ItemName *, char *);
int tar_update(int, ItemName *, char *);
int tar_extract(int, char *);
int tar_list(int);