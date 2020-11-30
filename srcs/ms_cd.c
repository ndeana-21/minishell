/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:49 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/01 00:44:31 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pwd(void)
{
	char	*tmp;

	if ((tmp = getcwd(NULL, 0)) != NULL)
	{
		free(tmp);
		replace_env("OLDPWD",
			ft_strdup((char *)(((t_env *)(find_env("PWD")->content))->val)));
		replace_env("PWD", getcwd(NULL, 0));
	}
	else
		chdir((char *)((t_env *)find_env("PWD")->content));
}

void		ms_cd(char *param)
{
	if (param == 0 && find_env("HOME") == NULL)
		print_error("HOME not set", 1);
	else if (param == 0)
		chdir((char *)((t_env *)find_env("HOME")->content));
	else
	{
		if (ft_strncmp(param, "~/", 2) == 0 ||
			(ft_strlen(param) == 1 && param[0] == '~'))
		{
			if (find_env("HOME") == NULL)
				print_error("HOME not set", 1);
			else
			{
				chdir((char *)((t_env *)find_env("HOME")->content));
				if (ft_strncmp(param, "~/", 2) == 0)
					param += 2;
				else
					param++;
			}
		}
		if (ft_strlen(param) > 0 && chdir(param) == -1)
			print_error(param, 1);
	}
	set_pwd();
}
