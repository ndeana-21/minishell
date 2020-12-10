/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:34:58 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/10 03:53:52 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			flag_echo(char **str)
{
	char	*buf;
	int		count;

	if (!str || !*str || !**str)
		return (FALSE);
	buf = *str;
	buf = ft_strpass(buf, " ");
	count = 0;
	if ((*buf) == '-')
	{
		while (*(++buf) == 'n')
			++count;
		if (!count || (*buf && ((*buf) != ' ')))
			return (FALSE);
		buf = ft_strpass(buf, " ");
		(*str) = buf;
		flag_echo(str);
		return (TRUE);
	}
	(*str) = buf;
	return (FALSE);
}

void		ms_echo(char *param)
{
	int	flag;

	if (!param || !(*param))
	{
		ft_putstr_fd("", 1);
		return ;
	}
	flag = flag_echo(&param);
	ft_putstr_fd(param, 1);
	if (!flag)
		ft_putstr_fd("\n", 1);
	g_exit = 0;
}
