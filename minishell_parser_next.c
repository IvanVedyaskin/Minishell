#include "minishell.h"

int	ft_strcmp_v2(char *cmp, char *str)
{
	int	i;

	i = 0;
	// printf ("%s    %s\n", cmp, str);
	while (str[i] && cmp[i])
	{
		if (str[i] != cmp[i])
			return (0);
		i++;
	}
	if (!cmp[i] && (is_token(str[i]) != WORD || str[i] == '$'))
		return (1);
	return (0);
}

char	*check_env_var(t_list *envp_list, char *str)
{
	t_list	*tmp;

	tmp = envp_list;
	while (tmp != NULL)
	{
		if (ft_strcmp_v2(tmp->key, str + 1))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

// int	ft_alloc_str(char **p, int token)
// {
// 	char	*tmp;

// 	if (token == SEP)
// 	{
// 		tmp = (char *)malloc(sizeof(char) + 1);
// 		tmp = **p;
// 		*(tmp + 1) = '\0'; 
// 	}
// 	else if (token == WORD)
// 	{
		 
// 	}
// 	*p = tmp;
// }

// int	ready_str_in_list(t_command **command)
// {
// 	t_command	*tmp;
// 	int			i;

// 	i = 0;
// 	tmp = *command;
// 	while (tmp != NULL)
// 	{
// 		if (tmp->str != NULL)
// 		{
// 			if (is_token(*(tmp->str)) == SEP)
// 			{
// 				if (i != 0 && tmp->next != NULL)

// 			}
// 		}
// 	}
// }

int	parser_next(t_command **command, t_info *info)
{
	t_command	*tmp;

	tmp = *command;
	while (tmp != NULL)
	{
		if (*(tmp->str) == '$')
		{
			if (is_token(*((tmp->str) + 1)) == WORD)
			{
				if (*((tmp->str) + 1) != '$' && *((tmp->str) + 1) != '?')
					tmp->str = check_env_var(info->envp_list, tmp->str);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}