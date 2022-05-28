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

extern char **environ;

# define NOTMALLOC -1


typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
}	t_list;

typedef struct s_token
{
	int				token;
	struct s_token	*next;
}	t_token;

typedef	struct s_command
{
	char				*str;
	struct s_command	*next;
}	t_command;

typedef struct s_info
{
	char			*res_word[7];	// ключевые слова
	char			**envp;     	// переменная окружения
	t_list			*envp_list;		// переменная окружения в листe
	t_token			*token;			// лист токенов
	int				envp_f;			// флаг на изменение envp. изменяется, если зменился envp_list
	int				exit_f;			// флаг на выход из программы
	int				status;			// когда вызываем $?
}	t_info;

typedef int (*t_builtin_ptr)(t_list *list, struct s_info *info);

t_builtin_ptr	builtins[7];	// массив функций ключевых слов

int			ft_strlen(char *str);
int			mem_lists(t_list **envp_list, char *str);
char		*key_value_cpy(char *dest, char *src, int flag);
int			key_value_mem(char *str, int flag);
int			start_lists(t_list **envp_list, char **envp);
void		print_error(int flag);
void		*ft_free_list(t_list **envp_list);
void		**ft_free_envp(char **envp);
int			ft_strlen(char *str);
int			ft_strcmp(char *str, char *cmp);
int			init(t_info *info, char **env);

int			lexer(t_info *info, char *line);
void		all_free(t_info *info, int flag, t_command **command);
int			is_token(char c);
t_command	*parser(t_info *info, char *p);
void		ft_check_print2(t_command **token);
int			check_fields(t_token **token);

int			parser_next(t_command **command, t_info *info);
// void	set_word(char *res_word[7]);
// int		init(t_info *info, char **env);
#endif