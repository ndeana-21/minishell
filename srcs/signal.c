/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:08:06 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/07 20:42:41 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char *buf;

	ft_putstr_fd("\033[34m", 1);
	ft_putstr_fd(((t_env *)find_env("USER")->content)->val, 1);
	ft_putstr_fd(" \033[32m", 1);
	if (!(buf = getcwd(NULL, 0)))
		error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
	ft_putstr_fd(buf, 1);
	free(buf);
	if (g_exit)
	{
		if (!(buf = ft_itoa(g_exit)))
			error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
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
		printf("hello\n");
		signum = wait(&status);
		g_exit = status / 256;
		ft_putstr_fd("\b\b  \b\b", 1);
		g_exit = 3;
		if (signum != -1)
			ft_putstr_fd("Quit: 3\n", 1);
		//kill(SIGTERM, 0);
	}
	else if (signum == SIGINT)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		write(1, "\n", 1);
		prompt();
		g_exit = 1;
	}
	return ;
}

void	set_signal(void)
{
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
	g_ret = NULL;
	g_exit = 0;
}
