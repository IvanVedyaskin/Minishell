#include "minishell.h"

// Все команды исполняются в подпроцессах. Исключение - builtins


// int	parser(t_info *info, char *p)
// {
// 	return (1);	
// }

char	*ft_readline(char *p)
{
	p = readline("minishell$ ");
	if (p && *p)
		add_history(p);
	return(p);
}

int	main(int ag, char **av, char **env)
{
	t_info	info;
	char	*p;

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
		break;
		// parser(&info, p);
	}
	// printf ("%p\n", info.token);
	all_free(&info, 1);
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