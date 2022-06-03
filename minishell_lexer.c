#include "minishell.h"

void	free_token(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
			free(*token);
			*token = NULL;
			*token = tmp;
		}
		free(*token);
		*token = NULL;
	}
}

void	ft_free_command(t_command **command)
{
	t_command	*tmp;

	tmp = *command;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		free(*command);
		*command = tmp;
	}
	free(*command);
	*command = NULL;
}

void	all_free(t_info *info, int flag, t_command **command)
{
	(void)	command;
	if (info->token != NULL)
		free_token(&info->token);
	if (command != NULL && *command != NULL)
		ft_free_command(command);
	if (flag == 1)
	{
		ft_free_envp(info->envp);
		ft_free_list(&info->envp_list);
	}
	if (flag < 1)
		print_error(info, flag);
}

int	create_list_token(t_token **token, int data)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp2 = *token;
	tmp = (t_token *)malloc(sizeof(t_token));
	if (!tmp)
		return (0);
	tmp->next = NULL;
	tmp->token = data;
	if (!tmp2)
		*token = tmp;
	else
	{
		while (tmp2->next != NULL)
			tmp2 = tmp2->next;
		tmp2->next = tmp;
	}
	return (1);
}

int	is_token(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || \
			c == '\f' || c == '\r' || c == ' ')
		return (SEP);
	else if (c == 39)
		return (FIELD);
	else if (c == 34)
		return (EXP_FIELD);
	else if (c == 62)
		return (REDIR_OUT);
	else if (c == 60)
		return (REDIR_IN);
	else if (c == 124)
		return (PIPE);
	else if (c != '\0')
		return (WORD);
	return (-1);
}

int	token_not_redir(char c, int flag, t_info *info)
{
	int	res;

	res = 1;
	if (is_token(c) == WORD)
	{
		if (flag != WORD)
			res = create_list_token(&info->token, WORD);
	}
	else if (is_token(c) == SEP)
	{
		if (flag != SEP)
			res = create_list_token(&info->token, SEP);
	}
	else if (is_token(c) == FIELD)
		res = create_list_token(&info->token, FIELD);
	else if (is_token(c) == EXP_FIELD)
		res = create_list_token(&info->token, EXP_FIELD);
	else if (is_token(c) == PIPE)
		res = create_list_token(&info->token, PIPE);
	flag = is_token(c);
	if (res == 0)
		all_free(info, 0, NULL);
	return (flag);
}

int	token_is_redir(char c, int *flag, int *i)
{
	if (is_token(c) == REDIR_OUT)
	{
		if (*flag == REDIR_OUT)
		{
			*flag = REDIR_APPEND;
			(*i)++;
		}
	}
	else if (is_token(c) == REDIR_IN)
	{
		if (*flag == REDIR_IN)
		{
			*flag = REDIR_INSOLUSION;
			(*i)++;
		}
	}
	return (1);
}

// int	skip_field2(t_token **token)
// {
// 	if ((*token)->token == 3)
// 	{
// 		*token = (*token)->next;
// 		while ((*token)->token != 3)
// 			*token = (*token)->next;
// 		return (1);
// 	}
// 	return (0);
// }

int	check_pipes_next(t_token *tmp)
{
	while (tmp != NULL)
	{
		skip_field(&tmp, EXP_FIELD);
		skip_field(&tmp, FIELD); 
		if (tmp->token == 8)
		{
			if (tmp->next == NULL)
				return (0);
			else if (tmp->next->token == 8)
				return (0);
			else if (tmp->next->token == 0 && tmp->next->next == NULL)
				return (0);
			else if (tmp->next->next != NULL && \
					tmp->next->next->token == 8 && tmp->next->token == 0)
				return (0);
		}
	tmp = tmp->next;
	}
	return (1);
}

int	check_pipes(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (tmp != NULL)
	{
		if (tmp->token == 8)
			return (0);
		else if (tmp->token == 0 && tmp->next != NULL && tmp->next->token == 8)
			return (0);
	}
	return (check_pipes_next(tmp));
}

int check_redirects(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp != NULL)
	{
		skip_field(&tmp, EXP_FIELD);
		skip_field(&tmp, FIELD);
		if (tmp->token >= 4 && tmp->token <= 7)
		{
			if (tmp->next == NULL)
				return (0);
			else if (tmp->next->token >= 4 && tmp->next->token <= 7)
				return (0);
			else if (tmp->next->token == 0 && tmp->next->next == NULL)
				return (0);
			else if (tmp->next->next != NULL && tmp->next->token == 0 && \
					tmp->next->next->token >= 4 && tmp->next->next->token <= 7)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	sub_check(int token, char *p, int *i)
{
	if (token == WORD)
	{
		while (is_token(p[*i]) == WORD)
		{
			if (p[*i] == 92 || p[*i] == ';')
				return (0);
			++*i;
		}
	}
	else
	{
		if (token == 2 || token == 3)
		{
			++*i;
			while (is_token(p[*i]) != token && p[*i])
				++*i;
			++*i;
		}
		else
		{
			while (is_token(p[*i]) == token && p[*i])
				++*i;
		}
	}
	return (1);
}

int	check_new_lines(t_token **token, char *p)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = *token;
	while (tmp != NULL)
	{
		if (!sub_check(tmp->token, p, &i))
			return (0);
		skip_field(&tmp, FIELD);
		skip_field(&tmp, EXP_FIELD);
		tmp = tmp->next;
	}
	return (1);
}

int	all_check(t_info *info, char *p)
{
	int	x;

	x = 0;
	if (!check_fields(&info->token))
		x = -1;
	else if (!check_pipes(&info->token))
		x = -2;
	else if (!check_redirects(&info->token) || !check_new_lines(&info->token, p))
		x = -3;
	if (x != 0)
		all_free(info, x, NULL);
	return (0);
}

int	lexer(t_info *info, char *line)
{
	int		i;
	int		flag;

	i = 0;
	flag = -1;
	while (line[i])
	{
		flag = token_not_redir(line[i], flag, info);
		if (flag == 4 || flag == 5)
		{
			token_is_redir(line[i + 1], &flag, &i);
			create_list_token(&info->token, flag);
		}
		i++;
	}
	all_check(info, line);
	return (1);
}
