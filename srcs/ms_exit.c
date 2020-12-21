/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:57:42 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/22 00:33:54 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_isdigitstr(char *str)
{
	int i;

	i = 0;
	while ((str[i] >= 7 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while ((str[i] >= 7 && str[i] < 13) || str[i] == 32)
		i++;
	if (str[i])
		return (0);
	return (1);
}

void			ms_exit(char **param)
{
	size_t	len;

	len = ft_pointer_len((void **)param);
	if (!(len))
		ft_putstr_fd("exit\n", 1);
	else if ((len == 1) && (ft_isdigitstr(param[0])))
	{
		g_exit = (ft_atoi(param[0]));
		ft_putstr_fd("exit\n", 1);
	}
	else if ((len > 1) && (ft_isdigitstr(param[0])))
	{
		ft_putendl_fd("minishell: exit: too many arguments", 1);
		return ;
	}
	else
	{
		ft_putstr_fd("minishell: exit: ", 1);
		ft_putstr_fd(param[0], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		exit(2);
	}
	exit(g_exit);
}
