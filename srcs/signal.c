/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:08:06 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/26 19:53:59 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char *buf;

	ft_putstr_fd("\033[34m", 1);
	if ((buf = (char *)find_env("USER")) &&
		(buf = (char *)((t_dl_list *)buf)->content) &&
		(buf = ((t_env *)buf)->val))
		ft_putstr_fd(buf, 1);
	else
		ft_putstr_fd("user", 1);
	ft_putstr_fd(" \033[32m", 1);
	if (!(buf = getcwd(NULL, 0)))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	ft_putstr_fd(buf, 1);
	free(buf);
	if (g_exit)
	{
		if (!(buf = ft_itoa(g_exit)))
			error_exit(EXIT_FAILURE, ERROR_MALLOC);
		ft_putstr_fd(" \033[1m\033[31m[", 1);
		ft_putstr_fd(buf, 1);
		ft_putstr_fd("]\033[0m", 1);
		free(buf);
	}
	ft_putstr_fd("\n\033[32m❱▶\033[0m ", 1);
}

void	signal_handler(int signum)
{
	int status;

	if (signum == SIGQUIT)
	{
		signum = wait(&status);
		g_exit = status / 256;
		ft_putstr_fd("\b\b  \b\b", 1);
		g_exit = 131;
		if (signum != -1)
			ft_putstr_fd("Quit: 3\n", 1);
	}
	else if (signum == SIGINT)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		write(1, "\n", 1);
		prompt();
		g_exit = 130;
	}
	return ;
}

void	set_signal(void)
{
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
	g_exit = 0;
}
