/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:08:06 by gselyse           #+#    #+#             */
/*   Updated: 2020/11/13 17:07:40 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
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
	ft_putstr(" ░▒▓\033[0;1;34m ");
	ft_putstr(path);
	ft_putstr(" \033[0;32m❱▶\033[0m ");
	free(pwd[0]);
	free(pwd[1]);
	free(path);
}
*/

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
		ft_putstr_fd("\b\b  \b\b", 1);
		write(1, '\n', 1);
		promt();
		g_exit = 1;
	}
}

void	set_signal(void)
{
	signal(SIGQUIT, (void *)signal_handler);
	signal(SIGINT, (void *)signal_handler);
}

#if 0
void  type_prompt(void)
{
  static int  first_time = 1;
  char    *cwd;

  if (first_time)
    ft_putstr_fd(" \e[1:1H\e[2J", STDOUT_FILENO);
  first_time = 0;
  ft_putstr_fd("\e[1mminishell:~", STDOUT_FILENO);
  cwd = getcwd(NULL, 0);
  ft_putstr_fd(cwd, 1);
  ft_putstr_fd("$\e[0m ", STDOUT_FILENO);
  free(cwd);
}
void  sigint_handler(int signum)
{
  int    stat;
  int    pid;

  pid = waitpid(-1, &stat, WNOHANG);
  if (signum == SIGINT)
  {
    write(1, "\n", 1);
    g_status = 1;
    if (pid)
      type_prompt();
  }
}

void  eof_handler(void)
{
  ft_putendl_fd("\nexit", 1);
  exit(EXIT_SUCCESS);
}

void  quit(int num)
{
  int    stat;
  int    pid;

  (void)num;
  pid = waitpid(-1, &stat, WNOHANG);
  if (!pid)
    ft_putstr_fd("Quit: 3\n", 1);
  else
    ft_putstr_fd("\b\b  \b\b", 1);
}
#endif
