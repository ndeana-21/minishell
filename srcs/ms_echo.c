/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:34:58 by gselyse           #+#    #+#             */
/*   Updated: 2020/11/18 21:26:03 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ms_echo(char *param)
{
	int 	flag;

	flag = 0;
	if (ft_strlen("-n") == ft_strcmp(param, "-n"))
	{
		flag = 1;
		param += 2;
		param = ft_strpass(param, " ");
	}
	ft_putstr_fd(param, 1);
	if (!flag)
		ft_putchar_fd('\n', 1);
}
