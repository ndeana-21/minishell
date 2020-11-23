/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:57:42 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/23 21:14:59 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#if 0

void	ms_exit(t_list *params)
{
	if (params)
		ft_putendl_fd(ERROR_PARAMS_MANY, 2);
	else
		exit(0);
}
#endif

//#if 0

static void		exit_error(int n, char *argv)
{
	if (n == 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		exit(EXIT_FAILURE);
	}
	if (n == 2)
	{
		ft_putstr_fd("minishell: exit:", 1);
		ft_putstr_fd(&argv[1], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		exit(EXIT_FAILURE);
	}
}

static int	ft_strln(char **s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

void	ms_exit(char *param)
{
	int i;
	int len;

	i = 0;
	len = ft_strln(param);
	if (len == 0)
		exit(EXIT_SUCCESS);
	else if (len > 2)
	{
		exit_error(1, NULL);
	}
	else
	{
		while (param[1])
		{
			if (ft_isalpha(param[++i]))
			{
				exit_error(2, &param[1]);
				return ;
			}
			else
				exit(ft_atoi(&param[1]));
		}
	}
}

//#endif