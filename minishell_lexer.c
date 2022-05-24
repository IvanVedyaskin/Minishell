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

void	all_free(t_info *info, int flag)
{
	if (info->token != NULL) 
		free_token(&info->token);
	if (flag == 1)
	{
		ft_free_envp(info->envp);
		ft_free_list(&info->envp_list);
	}
	if (flag == 0)
		print_error(0);
}

int	create_list_token(t_token **token, int data)
{
	t_token	*tmp;
	t_token *tmp2;

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
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
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
		all_free(info, 0);
	return (flag);
}

int token_is_redir(char c, int *flag, int *i)
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

int	lexer(t_info *info, char *line)
{
	int		i;
	int		flag;

	(void) info;
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
	return (0);
}