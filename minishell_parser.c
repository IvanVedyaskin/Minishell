#include "minishell.h"

int	create_command(t_command **command, char *date)
{
	t_command	*tmp1;
	t_command	*tmp2;

	tmp1 = *command;
	tmp2 = (t_command *)malloc(sizeof(t_command));
	if (tmp2 == NULL)
		return (0);
	tmp2->next = NULL;
	tmp2->str = date;
	if (tmp1 == NULL)
		*command = tmp2;
	else
	{
		while (tmp1->next != NULL)
			tmp1 = tmp1->next;
		tmp1->next = tmp2;
	}
	return (1);
}

int	ft_strcmp_v2(char *cmp, char *str)
{
	int	i;

	i = 0;
	while (str[i] && cmp[i])
	{
		if (str[i] != cmp[i])
			return (0);
		i++;
	}
	if (!cmp[i] && is_token(str[i]) != WORD)
		return (1);
	return (0);
}

int	check_env(char *str, t_list *envp_list, t_command **command)
{
	t_list	*tmp;
	int		flag;

	flag = 1;
	tmp = envp_list;
	while (tmp != NULL)
	{
		if (ft_strcmp_v2(tmp->key, str))
			return (create_command(command, &(tmp->value)));
		tmp = tmp->next;
	}
	flag = create_command(command, NULL);
	return (flag);
}

int	my_dollar(char *str, t_command **command, t_list *envp_list)
{
	int	i;
	int	flag;

	flag = 1;
	i = 0;
	if (str[i] == '$' || str[i] == '?')
		flag = create_command(command, &str[i]);
	else if (is_token(str[i]) == WORD)
		flag = check_env(str, envp_list, command);
	return (flag);
}

int	run_str(int token, char *p, t_command **command, t_list *envp_list)
{
	static int	i;
	int			tmp;

	tmp = i;
	if (token == 0)
	{
		while (is_token(p[i]) == SEP)
			i++;
		if (tmp != 0)
		{
			if (p[i])
				tmp = create_command(command, &(p[tmp]));
		}
	}
	else if (token == 1)
	{
		tmp = create_command(command, &(p[tmp]));
		while (is_token(p[i]) == WORD)
		{
			while (is_token(p[i]) == WORD)
			{
				if (p[i] == '$')
				{
					tmp = my_dollar(&(p[i + 1]), command, envp_list);
				}
				i++;
			}
			if (p[i] == '$')
				tmp = my_dollar(&(p[i + 1]), command, envp_list);
			else
				tmp = create_command(command, &(p[tmp]));
		}

	}
	return (tmp);
}

t_command	*parser(t_info *info, char *p)
{
	t_token		*token;
	t_command	*command;

	command = NULL;
	token = info->token;
	while (token != NULL)
	{
		run_str(is_token(token->token), p, command, info->envp_list);
		token = token->next;
	}
	return (1);	
}