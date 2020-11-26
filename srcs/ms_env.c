/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:50 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/26 13:33:42 by gselyse          ###   ########.fr       */
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
	ft_putstr_fd(g_ret, 1);//FIXMY debug
}

t_dl_list	*find_env(char *name)
{
	t_dl_list	*tmp_env;

	tmp_env = g_envlst;
	while (tmp_env)
	{
		if (ft_strsame(((t_env *)tmp_env->content)->name, name))
			return (tmp_env);
		tmp_env = (t_dl_list *)tmp_env->next;
	}
	return (NULL);
}
