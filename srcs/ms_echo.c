/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:34:58 by gselyse           #+#    #+#             */
/*   Updated: 2020/11/26 16:06:44 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			flag_echo(char **str)
{
	char	*buf;
	int		count;

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
	int 	flag;
	size_t	size;

	flag = 1;
	ft_strdel(&g_ret);
	if ((flag = (1 - flag_echo(&param))))
	{
		if (!(*param))
		{
			g_ret = ft_strdup("");
			return ;
		}
	}
	size = ft_strlen(param) + 1 + flag;
	if (!(g_ret = ft_calloc(sizeof(char), size)))
		error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
	ft_strappend(g_ret, param, sizeof(char) * size);
	if (flag)
		ft_strappend(g_ret, "\n", sizeof(char) * size);
	ft_putstr_fd(g_ret, 1);//FIXME это временно
}
