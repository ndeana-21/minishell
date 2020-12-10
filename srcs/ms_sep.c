/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_sep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 03:37:31 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/10 03:44:00 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_sep(t_dl_list *param)
{
	if (!(ft_dl_lstnnext(param, -1)->prev))
		shell_brach_command((char *)(ft_dl_lstnnext(param, -1)->content));
	if (!(ft_dl_lstnnext(param, 1)->next))
		shell_brach_command((char *)(ft_dl_lstnnext(param, 1)->content));
	else if (ft_strsame(ft_dl_lstnnext(param, 2)->content, ";"))
		shell_brach_command((char *)(ft_dl_lstnnext(param, 1)->content));
}
