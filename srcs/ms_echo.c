/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:34:58 by gselyse           #+#    #+#             */
/*   Updated: 2020/11/16 17:13:55 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ms_echo(char *param)
{
	int i;
	int flag;

	i = 1;
	flag = 0;
	while (param[i] != NULL)
	{
		if (ft_strpass(param[i], "-n") && i == 1)
			flag = 1;
		else
		{
			ft_putstr_fd(param[i], 1);
			if (param[i + 1] != NULL)
				ft_putstr_fd(" ", 1);
		}
		i++;
	}
	if (!flag)
		ft_putchar_fd("\n", 1);
}
