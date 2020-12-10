/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:45 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/23 19:20:50 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	ms_pwd(char *param)
{
	ft_putendl_fd(find_env("PWD"), 1);
}
*/
void	ms_pwd(char **param)
{
	char	*pwd;

	(void)param;
	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	//free(param);
	//return (1);
}
