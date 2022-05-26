#include "minishell.h"

void	set_word(char *res_word[7])
{
	res_word[0] = "echo";
	res_word[1] = "cd";
	res_word[2] = "pwd";
	res_word[3] = "export";
	res_word[4] = "unset";
	res_word[5] = "env";
	res_word[6] = "exit";
}

int	len_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		while (env[i][j] != '\0')
			j++;
		j = 0;
		i++;
	}
	return (++i);
}

void	ft_strcopy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	**init_envp(char **env)
{
	int		count;
	char	**envp;
	int		i;

	i = 0;
	count = len_env(env);
	envp = (char **)malloc(count * sizeof(char *));
	if (!envp)
		return (NULL);
	while (i < count - 1)
	{
		envp[i] = (char *)malloc(ft_strlen(env[i]) * sizeof(char));
		if (!*envp)
			return ((char **)ft_free_envp(envp));
		ft_strcopy(envp[i], env[i]);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

int	init(t_info *info, char **env)
{
	info->envp_list = NULL;
	set_word(info->res_word);
	info->envp = init_envp(env);
	if (info->envp == NULL)
		print_error(0);
	if (!start_lists(&info->envp_list, info->envp))
		print_error(0);
	info->token = NULL;
	return (1);
}
