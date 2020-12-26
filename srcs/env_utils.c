/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 03:37:08 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/26 22:32:44 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**create_env_exec(void)
{
	size_t		size;
	size_t		count;
	t_dl_list	*tmp_env;
	char		*tmp;
	char		**env;

	tmp_env = g_envlst;
	if (!(env = ft_calloc(sizeof(char *), ft_dl_lstsize(tmp_env) + 1)))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	count = 0;
	while (!tmp_env)
	{
		size = ft_strlen(((t_env *)tmp_env->content)->name) +
				ft_strlen(((t_env *)tmp_env->content)->val) + 2;
		if (!(tmp = ft_calloc(sizeof(char), size)))
			error_exit(EXIT_FAILURE, ERROR_MALLOC);
		ft_strappend(tmp, ((t_env *)tmp_env->content)->name, size);
		ft_strappend(tmp, "=", size);
		ft_strappend(tmp, ((t_env *)tmp_env->content)->val, size);
		env[count++] = tmp;
		tmp_env = (t_dl_list *)(tmp_env->next);
	}
	return (env);
}

void		free_env(void *env)
{
	if (env)
	{
		if (((t_env *)env)->name)
			free(((t_env *)env)->name);
		if (((t_env *)env)->val)
			free(((t_env *)env)->val);
		free(env);
	}
}

t_env		*create_env(char *str)
{
	size_t	count;
	t_env	*data;

	count = -1;
	if (!(data = ft_calloc(sizeof(t_env), 1)))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	while (str[++count])
		if (ft_strchr("=", str[count]))
		{
			str[count] = 0;
			if (!(data->val = ft_strdup(&(str[count + 1]))))
				error_exit(EXIT_FAILURE, ERROR_MALLOC);
			break ;
		}
	if (!(data->name = ft_strdup(str)))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	return (data);
}

void		replace_env(char *name, char *str)
{
	t_dl_list	*buf;
	t_env		*env;

	if (!(buf = find_env(name)))
	{
		if (!(env = ft_calloc(sizeof(t_env), 1)))
			error_exit(EXIT_FAILURE, ERROR_MALLOC);
		env->name = name;
		env->val = str;
		if (!(ft_dl_lstadd_back(&g_envlst, ft_dl_lstnew(env))))
			error_exit(EXIT_FAILURE, ERROR_MALLOC);
		return ;
	}
	ft_strdel(&(((t_env *)(buf->content))->val));
	ft_strdel(&name);
	((t_env *)(buf->content))->val = str;
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
