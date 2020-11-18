/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:50 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/18 19:53:48 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ms_env(char *str)
{
	t_dl_list	*tmp;

	tmp = g_envlst;
	while (tmp)
	{
		ft_putstr_fd(((t_env *)tmp->content)->name, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(((t_env *)tmp->content)->val, 1);
		tmp = tmp->next;
	}
}
