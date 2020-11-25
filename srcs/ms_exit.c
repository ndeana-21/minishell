/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:57:42 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/25 17:37:03 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//#if 0

static int			ft_strln(char **s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

static void			ft_freestrs(char **str)
{
	int i = 0;

	if (str[i])
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

static void			free_exit(void)
{
	ft_freestrs(g_envlst);
	exit(g_exit);
}

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

static void		exit_error(int n, char *argv)
{
	if (n == 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		free_exit();
	}
	if (n == 2)
	{
		ft_putstr_fd("minishell: exit:", 1);
		ft_putstr_fd(&argv[1], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		free_exit();
	}
}

void	ms_exit(char **param)
{
	int i;
	int len;

	i = 0;
	len = ft_strln(param);
	if (len == 0)
	{
		ft_putstr_fd("exit\n", 1);
		free_exit();
	}
	else if (len == 1)
	{
		g_exit = (ft_atoi(param));
		ft_putstr_fd("exit\n", 1);
		free_exit();
	}
	else if (len > 1 && (ft_isdigitstr(param)))
		//exit_error(len, param);
	{
		ft_putendl_fd("minishell: exit: too many arguments", 1);
		free_exit();
	}
	else
	{
		ft_putstr_fd("minishell: exit: ", 1);
		ft_putstr_fd(param, 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		g_exit = 255;
		free_exit();
	}
}

//#endif
