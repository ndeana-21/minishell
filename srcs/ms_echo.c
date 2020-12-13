/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:34:58 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/13 16:33:41 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t		flag_echo(char **str)
{
	ssize_t	count;
	ssize_t	i;

	count = -1;
	while (str[++count])
	{
		i = 0;
		if (str[count][i] == '-')
		{
			while (str[++count][++i])
				if (str[count][i] != 'n')
					break ;
			if (str[count][i])
				break ;
		}
		else
			break ;
	}
	return (count);
}

void		ms_echo(char **param)
{
	ssize_t	count;
	ssize_t	flag;

	if (!(param[0]))
	{
		ft_putstr_fd("", 1);
		return ;
	}
	flag = flag_echo(&(param[0]));
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
