/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_sup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <mmeredit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:10:52 by mmeredit          #+#    #+#             */
/*   Updated: 2022/07/08 17:13:35 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*add_to_top_sup(void *list, void *elem, int which_struct)
{
	t_commands			*tmp3;
	t_lists				*tmp4;	

	if (list == NULL)
		return (elem);
	if (which_struct == 3)
	{
		tmp3 = elem;
		tmp3->next = list;
		list = tmp3;
	}
	if (which_struct == 4)
	{
		tmp4 = elem;
		tmp4->next = list;
		list = tmp4;
	}
	return (list);
}

void	*add_to_end_sup(void *list, void *elem, int which_struct)
{
	t_commands			*tmp3;
	t_lists				*tmp4;	

	if (list == NULL)
		return (elem);
	if (which_struct == 3)
	{
		tmp3 = list;
		while (tmp3->next != NULL)
			tmp3 = tmp3->next;
		tmp3->next = elem;
	}
	if (which_struct == 4)
	{
		tmp4 = list;
		while (tmp4->next != NULL)
			tmp4 = tmp4->next;
		tmp4->next = elem;
	}
	return (list);
}
