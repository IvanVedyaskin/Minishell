#include "minishell.h"

int	mem_lists(t_list **envp_list, char *str)
{
	t_list	*tmp;
	t_list	*tmp2;

	// printf ("%p\n", *envp_list);
	tmp2 = *envp_list;
	tmp = (t_list *)malloc(sizeof(t_list));
	if (!tmp)
		return (0);
	tmp->next = NULL;
	tmp->key = (char *)malloc(key_value_mem(str, 0) * sizeof(char));
	tmp->value = (char *)malloc(key_value_mem(str, 1) * sizeof(char));
	if (!tmp->key || !tmp->value)
		return (0);
	tmp->key = key_value_cpy(tmp->key, str, 1);
	tmp->value = key_value_cpy(tmp->value, str, 0);
	if (*envp_list == NULL)
		*envp_list = tmp;
	else
	{
		while (tmp2->next != NULL)
			tmp2 = tmp2->next;
		tmp2->next = tmp;
	}
	return (1);
}

char	*key_value_cpy(char *dest, char *src, int flag)
{
	int	i;
	int	j;

	i = 0;
	if (flag)
	{
		while (src[i] != '=')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	else
	{
		j = 0;
		while (src[i] != '=')
			i++;
		while (src[++i])
			dest[j++] = src[i];
		dest[j] = '\0';
	}
	return (dest);
}

int	key_value_mem(char *str, int flag)
{
	int	i;
	int	tmp;

	i = 0;
	while (str[i] != '=')
		i++;
	if (flag)
	{
		while (str[i] != '=')
			i++;
		tmp = i++;
		while (str[i])
			i++;
		return (i - tmp);
	}
	return (++i);
}

int	start_lists(t_list **envp_list, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!mem_lists(envp_list, envp[i]))
			return (0);
		// 
		// printf ("%d\n", i);
		i++;
	}
	printf ("x1 = %p\n", *envp_list);
	return (1);
}