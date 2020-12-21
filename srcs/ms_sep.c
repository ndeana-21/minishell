/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_sep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 03:37:31 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/22 00:33:32 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_sep(t_dl_list *param)
{
	if (!(ft_dl_lstnnext(param, 1)->next))
		return ;
	else if (ft_strsame(ft_dl_lstnnext(param, 2)->content, ";"))
		run_cmd((ft_dl_lstnnext(param, 1)->content));
}
