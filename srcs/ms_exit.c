/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:57:42 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/12 20:05:18 by gselyse          ###   ########.fr       */
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

static void		exit_error(int n, char *argv)
{
	if (n == 1)
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
	if (n == 2)
	{
		ft_putstr_fd("minishell: exit:", 1);
		ft_putstr_fd(argv[1], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
	}
}

void	ms_exit(char **argv)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(argv);
	if (len == 1)
		exit(EXIT_SUCCESS);
	else if (len > 2)
	{
		exit_error(1, NULL);
	}
	else
	{
		while (argv[1])
		{
			if (ft_isalpha(argv[1][++i]))
			{
				exit_error(2, argv[1]);
				//return (1);
			}
			else
				exit(ft_atoi(argv[1]));
		}
	}
}