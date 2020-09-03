NAME = my_tar
CFLAGS = -Wall -Wextra -Werror
HEADER = .
SRCFILES = main.c cli.c task.c tar_extract.c tar_create.c tar_general.c tar_modify.c
SRCFLDR = .

$(NAME):
	gcc $(addprefix $(SRCFLDR)/,$(SRCFILES)) -I $(HEADER) -o $(NAME)

clean:
	@rm $(NAME)