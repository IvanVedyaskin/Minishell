#include "minishell.h"

int	is_not_word(int x)
{
	if (x < 48)
		return (1);
	else if (x > 90 && x < 97)
	{
		if (x != 95)
			return (1);
	}
	else if (x > 122 && x <= 127)
		return (1);
	else if (x > 57 && x < 65)
		return (1);
	return (0);
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
	if (!cmp[i] && (is_not_word(str[i]) || str[i] == '$'))
		return (1);
	return (0);
}

char	*check_env_var(t_list *envp_list, char *str)
{
	t_list	*tmp;

	tmp = envp_list;
	while (tmp != NULL)
	{
		if (ft_strcmp_v2(tmp->key, str))
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

char	*ft_copy(char *dst, char *src, char *env)
{
	int i;
	int j;
	int k;

	k = 0;
	j = 0;
	i = 0;
	while (src[j] && src[j] != '$')
		dst[i++] = src[j++];
	j++;
	while (!is_not_word(src[j]))
		++j;
//	printf ("%s %d\n", src, j);
	if (env != NULL)
	{
		while (env[k])
			dst[i++] = env[k++];
	}
	while (src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dst);
}

char	*re_command(char *str, char *env, int i)
{
    int		count;
//	int 	j;
	char	*new_str;

//	j = 0;
	count = i++;
	while (!is_not_word(str[i]))
		++i;
	if (env != NULL)
		new_str = (char *)malloc(sizeof (char) * (ft_strlen(str) - 1 - i + count + ft_strlen(env)));
	else
		new_str = (char *)malloc(sizeof (char) * (ft_strlen(str) - i + count));
	if (!new_str)
		return (NULL);
	new_str = ft_copy(new_str, str, env);
	free(str);
	return (new_str);
}

int	opening_dollar(t_command *cmd, int *i, t_info *info)
{
	char	*tmp;

	tmp = NULL;
	while (cmd->str[*i])
	{
		if (cmd->str[*i] == '$')
		{
			tmp = check_env_var(info->envp_list, &(cmd->str[*i + 1]));
			if (tmp != NULL)
				cmd->str = re_command(cmd->str, tmp, *i);
			else
				cmd->str = re_command(cmd->str, tmp, *i);
		}
		++*i;
	}
	return (0);
}

int	parser_next(t_command **command, t_info *info)
{
	t_command	*tmp;
	int			i;

	i = 0;
	tmp = *command;
	while (tmp != NULL)
	{
		if (tmp->flag == 1)
			opening_dollar(tmp, &i, info);
		i = 0;
		tmp = tmp->next;
	}
	return (0);
}