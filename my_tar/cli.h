#define OPTION_ERROR(option) fprintf(stderr, "Usage: Unknown option -%c\n", option);
#define NO_MODE_ERROR fprintf(stderr, "Usage: Must specify one of -c, -r, -t, -u, -x\n");
#define TWO_MODES_ERROR(prev, curr) fprintf(stderr, "Usage: Can't specify both -%c and -%c\n", prev, curr);

#define STDOUT_ERROR fprintf(stderr, "Usage: Cannot append to stdout\n");
#define NO_FILE_ERROR fprintf(stderr, "Usage: Option -f requires an argument\n");
#define NO_DIR_ERROR fprintf(stderr, "Usage: Missing argument for -C\n");
#define NO_ITEMS_ERROR fprintf(stderr, "Usage: No files or directories specified\n");

int cli_parse(int, char **, Task *);