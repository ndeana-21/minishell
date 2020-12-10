/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:47 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/10 03:54:38 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_export(char *param)
{
	t_env		*buf;
	t_dl_list	*tmp;

	if (!param || !(*param))
	{
		tmp = g_envlst;
		while (tmp)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(((t_env *)tmp->content)->name, 1);
			if (((t_env *)tmp->content)->val)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(((t_env *)tmp->content)->val, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
			tmp = (t_dl_list *)tmp->next;
		}
		return ;
	}
	if ((buf = create_env(param)))
		if (!(ft_dl_lstadd_back(&g_envlst, ft_dl_lstnew(buf))))
			error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
	g_exit = 0;
}
