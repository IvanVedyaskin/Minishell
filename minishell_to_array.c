#include "minishell.h"

int	count_args(t_token *token)
{
	int	counter;
	int	key;

	counter = 0;
	while (token != NULL)
	{
		key = token->token;
		if (key != 0 && key != 2 && key != 3)
			counter++;
		else if (token->token == FIELD || token->token == EXP_FIELD)
		{
			counter++;
			skip_field(&token, FIELD);
			skip_field(&token, EXP_FIELD);
		}
		token = token->next;
	}
	return (++counter);
}

int	list_to_array(int token, t_command *tmp)
{
	int		count;
	char	*p;
	char	*p1;
	int		i = 0;
	int		j = 0;

	count = 0;
	p = tmp->str;
	if (token == WORD)
	{
		while (is_token(p[i]) == WORD)
		{
			while (p[i] != '$' && is_token(p[i]) == WORD)
			{
				count++;
				i++;
			}
			if (p[i] == '$')
			{
				tmp = tmp->next;
				if (tmp->str != NULL)
				{
					if (*tmp->str == '$')
						count++;
					else
					{
						p1 = tmp->str;
						while (p1[j])
						{
							count++;
							j++;
						}
						tmp = tmp->next;
						p = tmp->str;
						i = -1;
					}
					i++;
					j = 0;
				}
			}
		}
	}
	return (++count);
}

int	parser(t_info *info, t_command **command)
{
	t_command	*tmp;
	(void)	info;
	// char		**str;

	tmp = *command;
	// if (tmp != NULL)
	// {
	// 	str = (char **)malloc(sizeof(char *) * count_args(info->token));
	// 	if (!str)
	// 		all_free(info, 0, command);
	// 	while (tmp != NULL)
	// 	{
	// 		printf ("NUMBERS = %d\n", list_to_array(is_token(*(tmp->str)), tmp));
	// 		break;
	// 	}
	// }
	return (0);
}