/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:50 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/10 03:53:39 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ms_env(char *param)
{
	t_dl_list	*tmp;

	if ((*param))
	{
		print_error(2, "env: too many arguments");
		return ;
	}
	tmp = g_envlst;
	while (tmp)
	{
		if ((((t_env *)tmp->content)->name) && (((t_env *)tmp->content)->val))
		{
			ft_putstr_fd(((t_env *)tmp->content)->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(((t_env *)tmp->content)->val, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = (t_dl_list *)tmp->next;
	}
	g_exit = 0;
}
