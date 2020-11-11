/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:45 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/11 22:55:47 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pwd(char *param)
{
	ft_putendl_fd(find_env("PWD"), 1);
}

// int		ms_pwd(char **argv)
// {
// 	char	*pwd;

// 	//(void)argv;
// 	pwd = getcwd(NULL, 0);
// 	ft_putendl_fd(pwd, 1);
// 	free(pwd);
// 	free(argv);
// 	return (1);
// }
