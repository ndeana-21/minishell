/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:50 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/14 00:32:18 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ms_env(char *str)//FIXME
{
	t_dl_list	*tmp;
	// t_env	*data;

	tmp = g_envlst;
	while (tmp)
	{
		ft_putchar_fd(((t_env *)tmp->content)->name, 1);
		ft_putchar_fd("=", 1);
		ft_putendl_fd(((t_env *)tmp->content)->val, 1);
		tmp->next;
	}
	
	// data = create_env(str);
	// if (find_env(data->name))
	// 	data = free_env(data);
	// else
	// 	ft_dl_lstadd_back(g_envlst, ft_dl_lstnew(data));
}
