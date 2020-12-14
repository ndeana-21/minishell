/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 21:56:07 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/14 15:12:50 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ms_exec(char **param)
{
	int		status;
	char	*path;
	pid_t	pid;
	DIR		*dir;

	if (!(path = find_path(param[0])))
	{
		ft_puterr(param[0], ": command not found", "", 127);
		return ;
	}
	if (!(pid = fork()))
	{
		if ((dir = opendir(path)))
			exit(ft_puterr(param[0], ": is a directory", "", 126));
		free(dir);
		if (execve(path, param, create_env_exec()) != -1)
			exit(EXIT_SUCCESS);
		if (errno == 13 || errno == 8)
			exit(ft_puterr(param[0], ": Permission denied", "", 126));
		exit(ft_puterr(param[0], ": ",strerror(errno), 2));
	}
	wait(&status);
	g_exit = status / 256;
	ft_strdel(&path);
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
		return (ft_strdup(param));
	paths = ft_split(g_path, ':');
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
