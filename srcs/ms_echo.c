/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:34:58 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/27 01:26:26 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t		flag_echo(char **str)
{
	size_t	flag;
	size_t	count;

	flag = 0;
	while (str[flag])
	{
		if (2 != (ft_strcmp(str[flag], "-n")))
			break ;
		count = 1;
		while (str[flag][++count])
			if (str[flag][count] != 'n')
				break ;
		if (str[flag][count])
			break ;
		flag++;
	}
	return (flag);
}

static void	echo_pwd(void)
{
	char	*pwd;

	if (!(pwd = getcwd(NULL, 0)))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	ft_putstr_fd(pwd, 1);
	free(pwd);
}

void		ms_echo(char **param)
{
	size_t	count;
	size_t	flag;

	if (!(param[0]))
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	flag = flag_echo(param);
	count = flag;
	while (param[count])
	{
		if (ft_strsame("~", param[count]))
			echo_pwd();
		else
			ft_putstr_fd(param[count], 1);
		if (param[count++])
			ft_putstr_fd(" ", 1);
	}
	if (!flag)
		ft_putstr_fd("\n", 1);
	g_exit = 0;
}
