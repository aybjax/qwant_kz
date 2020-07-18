#ifndef _COREWAR_H_
# define _COREWAR_H_

# define MEM_SIZE                (6 * 1024)
# define IDX_MOD                 512
# define MAX_ARGS_NUMBER         4
# define MAX_PLAYERS_NUMBE       4
# define PROCESS_MAX_SIZE        (MEM_SIZE / 6)

# define COMMENT_CHAR            '#'
# define LABEL_CHAR              ':'
# define DIRECT_CHAR             '%'
# define SEPARATOR_CHAR          ','

# define LABEL_CHARS             "abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING         ".name"
# define COMMENT_CMD_STRING      ".comment"

/*
** regs
*/
# define REG_NUMBER              16

/*
**
*/
typedef char                    args_type_t;

# define T_REG                   1 << 0
# define T_DIR                   1 << 1
# define T_IND                   1 << 2
# define T_LAB                   1 << 3

struct  cw_s
{
   char                         *mnemonique;
   char                         num_args;
   args_type_t                  type[MAX_ARGS_NUMBER];
   char                         code;
   int                          num_cycles;
   char                         *comment;
};

typedef struct op_s     op_t;

/*
** sizes
*/
# define IND_SIZE                1 << 1
# define REG_SIZE                1 << 2
# define DIR_SIZE                REG_SIZE

/*
 * Encoding argument types
 */
# define REG_CODE          1 //01
# define DIR_CODE          2 //10
# define IND_CODE          3 //11

/*
** cw_tab
*/
typedef struct  cw_s cw_t;

extern  cw_t    cw_tab[];


/*
** header
*/
# define PROG_NAME_LENGTH        128
# define COMMENT_LENGTH          2048
# define COREWAR_EXEC_MAGIC      0xea83f3

struct header_s
{
   int  magic;
   char prog_name[PROG_NAME_LENGTH + 1];
   int  prog_size;
   char comment[COMMENT_LENGTH + 1];
};

typedef struct header_s header_t;

/*
** live
*/
# define CYCLE_TO_DIE    1536
# define CYCLE_DELTA     50
# define NBR_LIVE        40
# define MAX_CHECKS      10

#endif
