/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:57:42 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/25 19:46:57 by ndeana           ###   ########.fr       */
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

	if (!(len = ft_pointer_len((void **)param)))
		ft_putstr_fd("exit\n", 1);
	else if ((len == 1) && (ft_isdigitstr(param[0])))
	{
		g_exit = (ft_atoi(param[0]));
		ft_putstr_fd("exit\n", 1);
	}
	else if ((len > 1) && (ft_isdigitstr(param[0])))
	{
		ft_puterr("exit: too many arguments", NULL, NULL, EXIT_FAILURE);
		return ;
	}
	else
		ft_puterr("exit: ", param[0], ": numeric argument required", 2);
	exit(g_exit);
}
