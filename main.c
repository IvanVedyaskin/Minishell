#include "minishell.h"

// Все команды исполняются в подпроцессах. Исключение - builtins

char	*ft_readline(char *p)
{
	p = readline("minishell$ ");
	if (p && *p)
		add_history(p);
	return (p);
}

void	ft_check_print(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
		{
			printf ("%d ", tmp->token);
			tmp = tmp->next;
		}
		printf ("%d\n", tmp->token);
	}
}

int	main(int ag, char **av, char **env)
{
	t_info		info;
	char		*p;
	t_command	*command;
	char 		**str;

	int i = 0;
	(void) ag;
	(void) av;
	p = NULL;
	if (!init(&info, env))
		return (write(2, "MEM NOT ALLOC!", 14));
	while (1)
	{
		p = ft_readline(p);
		// break;
		lexer(&info, p);
		ft_check_print(&info.token);
		command = pre_parser(&info, p);
		str = parser(&command);
		// parser(&info, &command);
//		ft_check_print2(&command);
		while (str[i] != NULL)
			printf ("%s\n", str[i++]);
		ft_free_envp(str);
//		ft_check_print2(&command);
		all_free(&info, 2, &command);
//		if (i == 0)
//		break;
//		i++;
		i = 0;
		free(p);
		p = NULL;
	}
	// printf ("%p\n", info.token);
	all_free(&info, 1, &command);
	free(p);
	return (0);
}

// FUTURE ENV
	// int	i;
	// int j;
	// int x;

	// j = 0;
	// i = 0;
	// while(i < 7)
	// {
	// 	x = ft_strcmp(info->res_word[i], p);
	// 	if (x == 1)
	// 	{
	// 		i = 0;
	// 		while (info->envp[i])
	// 		{
	// 			while (info->envp[i][j])
	// 			{
	// 				printf ("%c", info->envp[i][j]);
	// 				j++;
	// 			}
	// 			j = 0;
	// 			i++;
	// 			printf ("\n");
	// 		}
	// 		return (0);
	// 	}
	// 	i++;
	// }

// Провекра листа

	// t_list	*tmp;
	// tmp = info->envp_list;
	// while (tmp->next != NULL)
	// {
	// 	printf ("%s=", tmp->key);
	// 	printf ("%s\n", tmp->value);
	// 	tmp = tmp->next;
	// }

// Вывод токенов
	// while (info.token->next != NULL)
	// {
	// 	printf ("%d ",info.token->token);
	// 	info.token = info.token->next;
	// }
	// printf ("%d ",info.token->token);