/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:41 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/11 21:51:58 by gselyse          ###   ########.fr       */
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