/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:08:06 by gselyse           #+#    #+#             */
/*   Updated: 2020/11/19 16:13:38 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_putstr(char *str)
{
	int i;

	if (!str)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	promt(void)
{
	char *path;
	char *pwd[2];
	char *set;

	pwd[0] = getcwd(NULL, 0);
	set = !(ft_strncmp(pwd[0], "/Users/", 7)) ? ft_strjoin("/Users/", g_ret) : ft_strdup("/");
	pwd[1] = ft_strtrim(pwd[0], set);
	path = !(ft_strncmp(pwd[0], "/Users/", 7)) ? ft_strjoin("~/", pwd[1]) : ft_strjoin("/", pwd[1]);
	ft_putstr("\033[32;7m▓▒░ ");
	ft_putstr(g_ret);
	ft_putstr(" ░▒▓\033[0;1;34m \n");
	ft_putstr(path);
	ft_putstr(" \033[0;32m❱▶\033[0m ");
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
	}
	else if (signum == SIGINT)
	{
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

/*
void	input_ctrld()
{
	
}

int 	input(char **line)
{
	int ctrld;
	char *tmp;

	ctrld = 0;
	input_ctrld(ctrld, line);
	if (**line == '\n')
	{
		free(*line);
		return (0);
	}
	if (*line != NULL)
	{
		tmp = ft_strtrim(*line, " ");
		if (*line)
		{
			free(*line);
			*line = NULL;
		}
		*line = tmp;
	}
	return (1);
}
*/
