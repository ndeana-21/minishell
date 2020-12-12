/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:49 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/11 19:26:52 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pwd(void)
{
	char	*tmp;

	if ((tmp = getcwd(NULL, 0)))
	{
		free(tmp);
		replace_env("OLDPWD",
			ft_strdup((char *)(((t_env *)(find_env("PWD")->content))->val)));
		replace_env("PWD", getcwd(NULL, 0));
	}
	else
		chdir((char *)((t_env *)find_env("PWD")->content));
}

void		ms_cd_utilit(char *param)
{
	if (!(ft_strncmp(param, "~/", 2)) ||
		((ft_strlen(param) == 1) && (param[0] == '~')))
	{
		if (!(find_env("HOME")))
			print_error(1, "HOME not set");
		else
		{
			chdir((char *)((t_env *)find_env("HOME")->content));
			if (!(ft_strncmp(param, "~/", 2)))
				param += 2;
			else
				param++;
		}
	}
	if ((ft_strlen(param) > 0) && (chdir(param) == -1))
		print_error(1, param);
}

void		ms_cd(char **param)
{
	if (1 < ft_pointer_len((void **)param))
	{
		print_error(2, "cd: too many arguments");
		return ;
	}
	if (!(param[0]) && !(find_env("HOME")))
		print_error(1, "HOME not set");
	else if (!(param[0]))
		chdir((char *)((t_env *)find_env("HOME")->content));
	else
		ms_cd_utilit(param[0]);
	set_pwd();
	g_exit = 0;
}
