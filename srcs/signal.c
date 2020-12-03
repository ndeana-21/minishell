/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:08:06 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/03 16:04:57 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	promt(void)
{
	char *path;
	char *pwd[2];
	char *set;

	pwd[0] = getcwd(NULL, 0);
	set = !(ft_strncmp(pwd[0], "/Users/", 7)) ? ft_strjoin("/Users/", g_ret) : ft_strdup("/");
	pwd[1] = ft_strtrim(pwd[0], set);
	path = !(ft_strncmp(pwd[0], "/Users/", 7)) ? ft_strjoin("~/", pwd[1]) : ft_strjoin("/", pwd[1]);
	// ft_putstr_fd("\033[32;7m▓▒░ ", 1);
	// ft_putstr_fd(g_ret, 1);
	// ft_putstr_fd(" ░▒▓\033[0;1;34m \n", 1);
	ft_putstr_fd("\033[0;1;34m", 1);
	ft_putstr_fd(path, 1);
	ft_putstr_fd(" \033[0;32m❱▶\033[0m ", 1);
	free(pwd[0]);
	free(pwd[1]);
	free(path);
}


void	signal_handler(int signum)
{
	int status;

	if (signum == SIGQUIT)
	{
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
		promt();
		g_exit = 1;
	}
	return ;
}

void	set_signal(void)
{
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
	g_exit = 0;
}

