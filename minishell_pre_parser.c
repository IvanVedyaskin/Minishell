#include "minishell.h"

int	create_command(t_command **command, char *date, int flag)
{
	t_command	*tmp1;
	t_command	*tmp2;

	tmp1 = *command;
	tmp2 = (t_command *)malloc(sizeof(t_command));
	if (tmp2 == NULL)
		return (0);
	tmp2->next = NULL;
	tmp2->str = date;
	tmp2->flag = 1;
	if (flag == 0)
			tmp2->flag = 1;
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

// int	check_env(char *str, t_list *envp_list, t_command **command)
// {
// 	t_list	*tmp;
// 	int		flag;

// 	flag = 1;
// 	tmp = envp_list;
// 	while (tmp != NULL)
// 	{
// 		if (ft_strcmp_v2(tmp->key, str))
// 			return (create_command(command, tmp->value));
// 		tmp = tmp->next;
// 	}
// 	flag = create_command(command, NULL);
// 	return (flag);
// }

// int	my_dollar(char *str, t_command **command, t_list *envp_list)
// {
// 	int	i;
// 	int	flag;

// 	flag = 1;
// 	i = 0;
// 	if (str[i] == '$' || str[i] == '?')
// 		flag = create_command(command, &str[i]);
// 	else if (is_token(str[i]) == WORD)
// 		flag = check_env(str, envp_list, command);
// 	return (flag);
// }

char	*str_command(char *p, int tmp, int i, int flag)
{
	char	*str;
	int		j;

	j = 0;
	str = (char *)malloc(sizeof(char) * (i - tmp + 1));
	if (!str)
		return (NULL);
	if (flag == 1)
	{
		while (is_token(p[tmp]) == WORD)
			str[j++] = p[tmp++];
	}
	else if (flag == 2)
		str[j++] = p[tmp];
	else if (flag == 3)
	{
		str[j++] = p[tmp++];
		str[j++] = p[tmp++];
	}
	str[j] = '\0';
	return (str);
}

int	in_str_token(int token, char *p, t_command **command, int *i)
{
	int	tmp;

	tmp = *i;
	if (token == 0)
	{
		while (is_token(p[*i]) == SEP)
			(*i)++;
	}
	else if (token == 1)
	{
		while (is_token(p[*i]) == WORD)
			++*i;
		tmp = create_command(command, str_command(p, tmp, *i, 1), 1);
		if (tmp == 0)
			return (tmp);
	}
	return (tmp);
}

char	*str_command_fields(char *p, int tmp, int i)
{
	char	*str;
	int		j;

	j = 0;
	str = (char *)malloc(sizeof(char) * (i - tmp - 1));
	if (!str)
		return (NULL);
	++tmp;
	while (tmp < i - 1)
		str[j++] = p[tmp++];
	str[j] = '\0';
	return (str);
}

int	run_str(int token, char *p, t_command **command, int *i)
{
	int			tmp;

	tmp = *i;
	if (token == 0 || token == 1)
		tmp = in_str_token(token, p, command, i);
	else if (token == 8 || (token >= 4 && token <= 5))
		tmp = create_command(command, str_command(p, tmp, ++*i, 2), 0);
	else if (token == 6 || token == 7)
	{
		tmp = create_command(command, str_command(p, tmp, *i + 2, 3), 0);
		*i = *i + 2;
	}
	else
	{
		++*i;
		while (is_token(p[*i]) != token && p[*i])
			(*i)++;
		if (is_token(p[*i]) == token)
			++*i;
		tmp = create_command(command, str_command_fields(p, tmp, *i), 1);
	}
	return (tmp);
}

void	ft_check_print2(t_command **token)
{
	t_command	*tmp;

	tmp = *token;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
		{
			printf ("%s\n", tmp->str);
			tmp = tmp->next;
		}
		printf ("%s\n", tmp->str);
	}
}

int	check_fields(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp != NULL)
	{
		if (tmp->token == FIELD)
		{
			tmp = tmp->next;
			while (tmp != NULL && tmp->token != FIELD)
				tmp = tmp->next;
		}
		else if (tmp->token == EXP_FIELD)
		{
			tmp = tmp->next;
			while (tmp != NULL && tmp->token != EXP_FIELD)
			{
				tmp = tmp->next;
			}
		}
		if (tmp == NULL)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	skip_field(t_token **token, int x)
{
	if ((*token)->token == x)
	{
		*token = (*token)->next;
		while ((*token)->token != x)
			*token = (*token)->next;
		return (1);
	}
	return (0);
}

t_command	*pre_parser(t_info *info, char *p)
{
	t_token		*token;
	t_command	*command;
	int			flag;
	int			i;

	flag = 1;
	i = 0;
	command = NULL;
	token = info->token;
	while (token != NULL)
	{
		flag = run_str((token->token), p, &command, &i);
		skip_field(&token, FIELD);
		skip_field(&token, EXP_FIELD);
		token = token->next;
	}
	if (command != NULL)
		parser_next(&command, info);
	return (command);
}

// пока лист
// 	если &this == &next
//		значит, что дошел до следующей части.
// пока лист
//	Если this == $
//		если &this == &next
//			Значит это отправится на проверку переменной окружения
//	Если this == '
//		внутри данных ковычек все "" остаются и внутри не расерываются. Нужно доходить до самой дальней '. Отсальные 					одинарные ковычки опускаются
//