#include "minishell.h"

// Все команды исполняются в подпроцессах. Исключение - builtins

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

void	**ft_free(char **envp)
{
	while (*envp)
		free((*envp)--);
	free(envp);
	return (NULL);
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

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
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
			return ((char **)ft_free(envp));
		ft_strcopy(envp[i], env[i]);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

int	init(t_info *info, char **env)
{
	t_list	*tmp;

	info->envp_list = NULL;
	set_word(info->res_word);
	info->envp = init_envp(env);
	printf ("y1 = %p\n", info->envp_list);
	if (!info->envp)
		return (0);
	if (!start_lists(&info->envp_list, info->envp))
		return (0);
	tmp = info->envp_list;
	// printf ("y2 = %p\n", tmp->key);
	while (tmp->next != NULL)
	{
		printf ("%s=", tmp->key);
		printf ("%s\n", tmp->value);
		tmp = tmp->next;
	}
	return (1);
}

int	ft_strcmp(char *str, char *cmp)
{
	int i;

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

// int	parser(t_info *info, char *p)
// {
// 	return (1);
// }

char *ft_readline()
{
	char *p;

	p = readline("minishell ");
	if (p && *p)
		add_history(p);
	return (p);
}

int main(int ag, char **av, char **env)
{
	(void) ag;
	(void) av;
	(void) env;
	t_info	info;
	(void) info;
	char	*p;

	if (!init(&info, env))
		return (write(2, "MEM NOT ALLOC!", 14));
	while (1)
	{
		p = ft_readline();
		// parser(&info, p);
	}
}


// FUTURE ENV
	// int	i;
	// int j;
	// int x;

	// j = 0;
	// i = 0;
	// while(i < 7)
	// {
	// 	x = ft_strcmp(info->res_word[i], p);
	// 	if (x == 1)
	// 	{
	// 		i = 0;
	// 		while (info->envp[i])
	// 		{
	// 			while (info->envp[i][j])
	// 			{
	// 				printf ("%c", info->envp[i][j]);
	// 				j++;
	// 			}
	// 			j = 0;
	// 			i++;
	// 			printf ("\n");
	// 		}
	// 		return (0);
	// 	}
	// 	i++;
	// }