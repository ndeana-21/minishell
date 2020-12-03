/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:50 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/02 01:09:39 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t		len_lstenv(t_dl_list *tmp, size_t plus)
{
	size_t		size;

	size = 0;
	while (tmp)
	{
		size += ft_strlen(((t_env *)tmp->content)->name) + 1;
		size += ft_strlen(((t_env *)tmp->content)->val) + 1;
		size += plus;
		tmp = (t_dl_list *)tmp->next;
	}
	return (size);
}

void		ms_env(char *str)
{
	t_dl_list	*tmp;
	size_t		size;

	(void)str;
	tmp = g_envlst;
	ft_strdel(&g_ret);
	size = len_lstenv(tmp, 2);
	if (!(g_ret = ft_calloc(sizeof(char), size + 1)))
		error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
	while (tmp)
	{
		if ((((t_env *)tmp->content)->name) && (((t_env *)tmp->content)->val))
		{
			ft_strappend(g_ret, ((t_env *)tmp->content)->name, size * sizeof(char));
			ft_strappend(g_ret, "=", size * sizeof(char));
			ft_strappend(g_ret, ((t_env *)tmp->content)->val, size * sizeof(char));
			ft_strappend(g_ret, "\n", size * sizeof(char));
		}
		tmp = (t_dl_list *)tmp->next;
	}
	ft_putstr_fd(g_ret, 1);//FIXME debug
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
