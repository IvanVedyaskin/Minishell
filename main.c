/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <mmeredit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:39:19 by mmeredit          #+#    #+#             */
/*   Updated: 2022/07/08 17:18:42 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_command	*pre_parser(t_info *info, char *p)
{
	t_command	*command;
	int			i;

	i = 0;
	command = NULL;
	while (p[i])
		run_str(is_token(p[i]), p, &command, &i);
	if (command != NULL)
		parser_next(&command, info);
	return (command);
}

char	*ft_readline(char *p, t_info *info)
{
	p = readline("minishell$ ");
	if (p)
		add_history(p);
	else
	{
		printf ("exit\n");
		all_free(info, 1, NULL);
		exit(EXIT_SUCCESS);
	}
	return (p);
}

void	ft_minishell(char *p, t_info *info, t_command *command)
{
	char	**str;

	str = NULL;
	if (p != NULL && !ft_strcmp_v2(p, "\n"))
	{
		if (lexer(info, p) == 0)
		{
			command = pre_parser(info, p);
			str = parser(&command);
			if (str[0] != NULL)
				ft_pipex(str, info);
		}
		str = ft_free_array(str);
		all_free(info, 2, &command);
	}
}

int	main(int ag, char **av, char **env)
{
	t_info		info;
	char		*p;
	t_command	*command;

	(void) av;
	(void) ag;
	p = NULL;
	command = NULL;
	if (!init(&info, env))
		return (write(2, "MEM NOT ALLOC!", 14));
	signal_handlers();
	while (!info.exit_f)
	{
		p = ft_readline(p, &info);
		ft_minishell(p, &info, command);
		free(p);
		p = NULL;
	}
	return (0);
}
