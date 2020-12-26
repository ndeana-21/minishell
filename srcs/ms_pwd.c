/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:45 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/27 00:33:28 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pwd(char **param)
{
	char	*pwd;

	(void)param;
	if (!(pwd = getcwd(NULL, 0)))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	g_exit = 0;
}
