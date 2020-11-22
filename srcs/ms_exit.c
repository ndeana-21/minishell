/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:57:42 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/22 11:34:18 by ndeana           ###   ########.fr       */
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
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
	if (n == 2)
	{
		ft_putstr_fd("minishell: exit:", 1);
		ft_putstr_fd(&argv[1], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
	}
}

void	ms_exit(char *param)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(param);
	if (len == 1)
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
				//return (1);
			}
			else
				exit(ft_atoi(&param[1]));
		}
	}
}

//#endif