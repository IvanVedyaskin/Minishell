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
		tmp = create_command(command, &(p[tmp]));
		if (tmp == 0)
			return (tmp);
		while (is_token(p[++(*i)]) == WORD)
		{
			if (p[*i] == '$' || (is_not_word(p[*i]) && p[*i] != '?'))
				tmp = create_command(command, &(p[*i]));
		}
	}
	return (tmp);
}

int	run_str(int token, char *p, t_command **command, int *i)
{
	int			tmp;

	tmp = *i;
	if (token == 0 || token == 1)
		tmp = in_str_token(token, p, command, i);
	else if (token == 8 || (token >= 3 && token <= 5))
	{
		tmp = create_command(command, &(p[tmp]));
		(*i)++;
	}
	else if (token == 6 || token == 7)
	{
		tmp = create_command(command, &(p[tmp]));
		*i = *i + 2;
	}
	else
	{
		tmp = create_command(command, &(p[(*i)++]));
		while (is_token(p[*i]) != 2 && p[*i])
			(*i)++;
		if (is_token(p[*i]) == 2)
			++*i;
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