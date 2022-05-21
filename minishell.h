#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <readline/history.h>

# define SEP 0
# define WORD 1
# define FIELD 2
# define EXP_FIELD 3
# define REDIR_OUT 4
# define REDIR_IN 5
# define REDIR_APPEND 6
# define REDIR_INSOLUSION 7
# define PIPE 8


# define NOTMALLOC -1


typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
}	t_list;

typedef struct s_info
{
	char			*res_word[7];	// ключевые слова
	char			**envp;     	// переменная окружения
	t_list			*envp_list;		// переменная окружения в листe
	int				envp_f;			// флаг на изменение envp. изменяется, если зменился envp_list
	int				exit_f;			// флаг на выход из программы
	int				status;			// когда вызываем $?
}	t_info;

typedef int (*t_builtin_ptr)(t_list *list, struct s_info *info);

t_builtin_ptr	builtins[7];	// массив функций ключевых слов

int		parser(t_info *info, char *p);
int		ft_strlen(char *str);
int		mem_lists(t_list **envp_list, char *str);
char	*key_value_cpy(char *dest, char *src, int flag);
int		key_value_mem(char *str, int flag);
int		start_lists(t_list **envp_list, char **envp);

#endif