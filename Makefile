NAME = minishell

SRC = main.c minishell_llist.c

SRC_OBJ = $(SRC:%.c=%.o)

SRC_D = $(SRC:%.c=%.d)

CC = cc

CFLAGS = -MD -Wall -Wextra -Werror

FSA = -fsanitize=thread

RM = rm -f

all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(SRC_OBJ)
	$(CC) $(SRC_OBJ) -lreadline -o $@

clean: 
	$(RM) $(SRC_OBJ) $(SRC_D)

fclean: clean
	$(RM) $(NAME)

-include $(SRC_D)

re: fclean all

.PHONY: all clean fclean re