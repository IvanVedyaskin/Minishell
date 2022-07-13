/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:15 by hbecki            #+#    #+#             */
/*   Updated: 2022/07/08 15:52:40 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	some_free(int *match_flag, t_lists **tmp_env, char **key_value)
{
	*match_flag = 1;
	free((*tmp_env)->value);
	(*tmp_env)->value = ft_create_str(key_value[1]);
	free(key_value[0]);
	free(key_value[1]);
}

int	ft_pipex(char **arr_of_comands, t_info *info)
{
	t_process_config	*process_config;
	char				**paths;
	char				**commands;

	commands = NULL;
	process_config = NULL;
	process_config = ft_parce_commands(arr_of_comands, process_config);
	if (process_config == NULL)
		return (0);
	if (ft_lonely_biultin(process_config, info))
		return (1);
	paths = ft_get_path_new(info->envp);
	process_config = ft_multi_exec(process_config, \
commands, info, paths);
	ft_close_pipes(process_config);
	info = ft_waiter(process_config, info);
	ft_split_free(paths);
	ft_free_processes(process_config);
	return (0);
}
