/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:49 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/30 21:13:59 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
void		ms_cd(char *argv)
{
		char *path;

		if (argv[1])
		{
			path = get_env_pwd();
			if (chdir(path) == -1)
				//ft_putendl_fd();
		}



}
*/

void		ms_cd(char *argv)
{
	int		res;

	res = 0;
	if (!argv[1] || (ft_strcmp(argv[1], "~") == 0))
	{
		while (g_envlst)
		{
			if (ft_strncmp(g_envlst, "HOME", 4) == 0)
			{
				res = chdir(&g_envlst[5]);
				return ;
			}
		}
	}
	else
		res = chdir(argv[1]);
	if (res != 0)
		printf("-minishell: cd: %s: No such file or directory\n", argv[1]);
	return ;
}


/*
static int		ft_puterr(char *s1, char *s2, char *s3, int err)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putendl_fd(s3, 2);
	g_exit = 1;
	return (err);
}


void	ft_change(void)
{
	char	*tmp[2];

	tmp[0] = get_env_pwd("PWD");
	if (tmp[0] == NULL)
		tmp[0] = ft_strdup("");
	tmp[1] = ft_strjoin("OLDPWD=", tmp[0]);
	ms_export(tmp[1]);
	free(tmp[0]);
	free(tmp[1]);
	tmp[0] = getcwd(0, 1024);
	tmp[1] = ft_strjoin("PWD=", tmp[0]);
	ms_export(tmp[1]);
	free(tmp[0]);
	free(tmp[1]);
	g_exit = 0;
}

int		its_fine(char **param)
{
	if (param[1] == NULL || ((param[1] != NULL) && (ft_strlen(param[1]) == 1)
		&& (param[1][0] == '~')))
		return (1);
	else
	{
		return (0);
	}
}

int		ms_cd(char *param)
{
	char	*path;

	path = 0;
	if (its_fine(param))
	{
		path = find_env("HOME");
		if (path == NULL)
			return (ft_puterr("cd: ", "HOME not set", "", 1));
		if (chdir(path) == -1)
		{
			if (errno == 13 || errno == 8)
				return (ft_puterr("cd: ", param[1], ": Permission denied", 126));
			return (ft_puterr("cd: ", param[1], ": No such file", 127));
		}
	}
	else if (chdir(param[1]) == -1)
	{
		if (errno == 13 || errno == 8)
			return (ft_puterr("cd: ", param[1], ": Permission denied", 126));
		return (ft_puterr("cd: ", param[1], ": No such file", 127));
	}
	ft_change();
	return (0);
}
*/
