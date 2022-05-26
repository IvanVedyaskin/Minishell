#include "minishell.h"

void	*ft_free_list(t_list **envp_list)
{
	t_list	*tmp;

	tmp = *envp_list;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		free((*envp_list)->key);
		free((*envp_list)->value);
		free(*envp_list);
		*envp_list = tmp;
	}
	free((*envp_list)->key);
	free((*envp_list)->value);
	free((*envp_list));
	*envp_list = NULL;
	return (NULL);
}

void	**ft_free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		free(envp[i++]);
	free(envp);
	envp = NULL;
	return (NULL);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (++i);
}

int	ft_strcmp(char *str, char *cmp)
{
	int	i;

	i = 0;
	while (str[i] && cmp[i])
	{
		if (str[i] != cmp[i])
			return (0);
		i++;
	}
	if (!str[i] && !cmp[i])
		return (1);
	return (0);
}
