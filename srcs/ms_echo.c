/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:34:58 by gselyse           #+#    #+#             */
/*   Updated: 2020/11/22 11:52:40 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ms_echo(char *param)
{
	int 	flag;
	size_t	size;

	flag = 1;
	ft_strdel(&g_ret);
	if (ft_strlen("-n") == (size_t)ft_strcmp(param, "-n"))
	{
		flag = 0;
		param += 2;
		if (!(*param))
		{
			g_ret = ft_strdup("");
			return ;
		}
		if (*param != ' ')
			param -= 2;
		param = ft_strpass(param, " ");
	}
	size = ft_strlen(param) + 1 + flag;
	if (!(g_ret = ft_calloc(sizeof(char), size)))
		error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
	ft_strappend(g_ret, param, sizeof(char) * size);
	if (flag)
		ft_strappend(g_ret, "\n", sizeof(char) * size);
	ft_putstr_fd(g_ret, 1);
}
