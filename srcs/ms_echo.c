/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:34:58 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/15 16:46:41 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t		flag_echo(char **str)
{
	size_t	flag;
	size_t	count;

	flag = -1;
	while (str[++flag])
	{
		if (2 < (ft_strcmp(str[flag], "-n")))
			break ;
		count = 1;
		while (str[flag][++count])
			if (str[flag][count] != 'n')
				break ;
		if (str[flag][count])
			break ;
	}
	return (flag);
}

void		ms_echo(char **param)
{
	size_t	count;
	size_t	flag;

	if (!(param[0]))
	{
		ft_putstr_fd("", 1);
		return ;
	}
	flag = flag_echo(param);
	count = flag;
	while (param[count])
	{
		ft_putstr_fd(param[count], 1);
		if (param[count++])
			ft_putstr_fd(" ", 1);
	}
	if (!flag)
		ft_putstr_fd("\n", 1);
	g_exit = 0;
}
