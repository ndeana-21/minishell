/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:50 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/22 11:38:27 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ms_env(char *str)
{
	t_dl_list	*tmp;
	size_t		size;

	(void)str;
	tmp = g_envlst;
	size = 0;
	ft_strdel(&g_ret);
	while (tmp)
	{
		size += ft_strlen(((t_env *)tmp->content)->name) + 1;
		size += ft_strlen(((t_env *)tmp->content)->val) + 1;
		tmp = (t_dl_list *)tmp->next;
	}
	if (!(g_ret = ft_calloc(sizeof(char), size + 1)))
		error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
	tmp = g_envlst;
	while (tmp)
	{
		ft_strappend(g_ret, ((t_env *)tmp->content)->name, size * sizeof(char));
		ft_strappend(g_ret, "=", size * sizeof(char));
		ft_strappend(g_ret, ((t_env *)tmp->content)->val, size * sizeof(char));
		ft_strappend(g_ret, "\n", size * sizeof(char));
		tmp = (t_dl_list *)tmp->next;
	}
}
