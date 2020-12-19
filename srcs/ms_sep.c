/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_sep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 03:37:31 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/19 21:14:42 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_sep(t_dl_list *param)
{
	if (!(ft_dl_lstnnext(param, 1)->next))
		return;
	else if (ft_strsame(ft_dl_lstnnext(param, 2)->content, ";"))
		shell_brach_cmd((ft_dl_lstnnext(param, 1)->content));
}
