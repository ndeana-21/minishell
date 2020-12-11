/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 21:56:07 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/11 17:28:33 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ms_exec(char *param)
{
	int		status;
	char	*path;
	char	**elem;
	pid_t	pid;

	elem = ft_split(param, ' ');
	if (!(path = find_path(elem[0])))
	{
		ft_puterr(elem[0], ": command not found", "", 127);
		return ;
	}
	if (!(pid = fork()))
	{
		if (opendir(path) != NULL)
			exit(ft_puterr(elem[0], ": is a directory", "", 126));
		if (execve(path, elem, g_envlst) == -1)
		{
			if (errno == 13 || errno == 8)
				exit(ft_puterr(elem[0], ": Permission denied", "", 126));
			//ft_putstr_fd("minishell :", 1);
			exit(ft_puterr(elem[0], ": command not found", "", 127));
		}
		exit(EXIT_SUCCESS);
	}
	wait(&status);
	g_exit = status / 256;
}

static int	is_absolute_path(char *path)
{
	struct stat	s;

	if (stat(path, &s) == 0)
		return (1);
	else
		return (0);
}

char		*find_path(char *param)
{
	int			i;
	char		*tmp;
	char		*path;
	char		**paths;
	struct stat	s;

	if (is_absolute_path(param))
		return (param);
	if (!(tmp = ((t_env *)(find_env("PATH")->content))->val))
		return (NULL);
	paths = ft_split(tmp, ':');
	i = -1;
	while (paths[++i] && paths)
	{
		tmp = ft_strjoin("/", param);
		path = ft_strjoin(paths[i], tmp);
		free(tmp);
		if (stat(path, &s) == 0)
		{
			ft_freestrs(paths);
			return (path);
		}
		free(path);
	}
	ft_freestrs(paths);
	return (ft_strdup(param));
}
//TODO твое