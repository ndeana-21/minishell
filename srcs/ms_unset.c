/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:41 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/12 00:24:43 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_unset(char **str)
{
	t_dl_list	*tmp;
	ssize_t		count;

	g_exit = 0;
	if (!str)
		return ;
	count = -1;
	while (str[++count])
		if ((tmp = find_env(str[count])))
			ft_dl_lstdelone(tmp, free_env);
}
