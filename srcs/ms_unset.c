/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:41 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/11 21:00:17 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_unset(char *str)
{
	t_dl_list	*tmp;

	if (!(tmp = find_env(str)))
		return ;
	ft_dl_lstdelone(tmp, free);
}