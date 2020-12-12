/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:47 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/12 02:49:49 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	printing_export(void)
{
	t_dl_list	*tmp;

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
}

void		ms_export(char **param)
{
	t_env		*buf;
	ssize_t		count;

	if (!param || !(*param) || !(**param))
	{
		printing_export();
		return ;
	}
	count = -1;
	while (param[++count])
	{
		if ((buf = create_env(param[0])))
			if (!(ft_dl_lstadd_back(&g_envlst, ft_dl_lstnew(buf))))
				error_exit(EXIT_FAILURE, ERROR_MALLOC);
	}
	g_exit = 0;
}
