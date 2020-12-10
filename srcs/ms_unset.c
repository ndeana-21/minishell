/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:41 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/10 03:55:12 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_unset(char *str)
{
	t_dl_list	*tmp;

	g_exit = 0;
	if (!(tmp = find_env(str)))
		return ;
	ft_dl_lstdelone(tmp, free_env);
}
