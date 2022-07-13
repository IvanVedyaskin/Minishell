/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_list_related_funcs.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <mmeredit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:49:41 by hbecki            #+#    #+#             */
/*   Updated: 2022/07/08 17:11:48 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*add_to_end(void *list, void *elem, int which_struct)
{
	t_process_config	*tmp1;
	t_file				*tmp2;

	if (list == NULL)
		return (elem);
	if (which_struct == 1)
	{
		tmp1 = list;
		while (tmp1->next != NULL)
			tmp1 = tmp1->next;
		tmp1->next = elem;
	}
	if (which_struct == 2)
	{
		tmp2 = list;
		while (tmp2->next != NULL)
			tmp2 = tmp2->next;
		tmp2->next = elem;
	}
	if (which_struct > 2)
		list = add_to_end_sup(list, elem, which_struct);
	return (list);
}

void	*add_to_top(void *list, void *elem, int which_struct)
{
	t_process_config	*tmp1;
	t_file				*tmp2;	

	if (list == NULL)
		return (elem);
	if (which_struct == 1)
	{
		tmp1 = elem;
		tmp1->next = list;
		list = tmp1;
	}	
	if (which_struct == 2)
	{
		tmp2 = elem;
		tmp2->next = list;
		list = tmp2;
	}
	if (which_struct > 2)
		list = add_to_top_sup(list, elem, which_struct);
	return (list);
}

t_process_config	*ft_create_proc_elem(int number)
{
	t_process_config	*elem;

	elem = (t_process_config *)malloc(sizeof(t_process_config));
	ft_check_malloc(elem);
	elem->command = NULL;
	elem->heredoc = NULL;
	elem->number_of_proc = number;
	elem->read_files = NULL;
	elem->out_files = NULL;
	elem->im_last_flag = 0;
	elem->from_prev_pipe = -1;
	elem->to_next_pipe = -1;
	elem->here_doc_pipes = NULL;
	elem->next = NULL;
	return (elem);
}

t_file	*ft_create_file_elem(char *file_name, int type_flag)
{
	t_file	*elem;

	elem = (t_file *)malloc(sizeof(t_file));
	ft_check_malloc(elem);
	elem->file = file_name;
	elem->type_flag = type_flag;
	elem->next = NULL;
	return (elem);
}

t_commands	*ft_create_command_elem(char *command_name)
{
	t_commands	*elem;

	elem = (t_commands *)malloc(sizeof(t_commands));
	ft_check_malloc(elem);
	elem->command = command_name;
	elem->next = NULL;
	return (elem);
}
