/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:47 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/02 01:17:24 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env(char *str)
{
	size_t	count;
	t_env	*data;

	count = -1;
	if (!(data = ft_calloc(sizeof(t_env), 1)))
		error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
	while (str[++count])
		if (ft_strchr("=", str[count]))
		{
			str[count] = 0;
			if (!(data->val = ft_strdup(&(str[count + 1]))))
				error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
			break ;
		}
	if (!(data->name = ft_strdup(str)))
		error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
	return (data);
}

void		replace_env(char *name, char *str)
{
	t_dl_list	*buf;
	t_env		*env;

	if (!(buf = find_env(name)))
	{
		if (!(env = ft_calloc(sizeof(t_env), 1)))
			error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
		env->name = name;
		env->val = str;
		if (!(ft_dl_lstadd_back(&g_envlst, ft_dl_lstnew(env))))
			error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
		return ;
	}
	ft_strdel(&(((t_env *)(buf->content))->val));
	((t_env *)(buf->content))->val = str;
}

void	ms_export(char *param)
{
	t_env	*buf;
	size_t	size;
	t_dl_list	*tmp;

	if (!param || !(*param))
	{
		tmp = g_envlst;
		ft_strdel(&g_ret);
		size = len_lstenv(tmp, 15);
		if (!(g_ret = ft_calloc(sizeof(char), size + 1)))
			error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
		while (tmp)
		{
			ft_strappend(g_ret, "declare -x ", size * sizeof(char));
			ft_strappend(g_ret, ((t_env *)tmp->content)->name, size * sizeof(char));
			if (((t_env *)tmp->content)->val)
			{
				ft_strappend(g_ret, "=\"", size * sizeof(char));
				ft_strappend(g_ret, ((t_env *)tmp->content)->val, size * sizeof(char));
				ft_strappend(g_ret, "\"", size * sizeof(char));
			}
			ft_strappend(g_ret, "\n", size * sizeof(char));
			tmp = (t_dl_list *)tmp->next;
		}
		ft_putstr_fd(g_ret, 1);//FIXME debug
	}
	else
		if ((buf = create_env(param)))
			if (!(ft_dl_lstadd_back(&g_envlst, ft_dl_lstnew(buf))))
				error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
}
