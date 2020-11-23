/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:41 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/22 23:29:25 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*free_env(t_env *env)
{
	if (env)
	{
		free(env->name);
		free(env->val);
		free(env);
	}
	return (NULL);
}

void	ms_unset(char *str)
{
	t_dl_list	*tmp;

	if (!(tmp = find_env(str)))
		return ;
	ft_dl_lstdelone(tmp, free_env);
}
