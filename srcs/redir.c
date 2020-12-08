/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:25:18 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/08 17:15:56 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
int		search_redir(char **param)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (param[i])
	{
		if ((ft_strpass(param[i], ">") || (ft_strpass(param[i], ">>") || (ft_strpass(param[i], "<")))))
			count++;
		i++;
	}
	return (count);
}

int		type_redir(char *param)
{
	if (ft_strpass(param, ">"))
	{
		flag_r = 1;
		return (1);
	}
	else if (ft_strpass(param, ">>"))
	{
		flag_r = 2;
		return (1);
	}
	else if (ft_strpass(param, "<"))
	{
		flag_r = 3;
		return (1);
	}
	else
		return (-1);
}
*/

int		exec_redir()

void	open_files(char *param)
{
	int i;
	int fd;

	i = 0;
	while (param[i])
	{
		if (flag_r == 1)
			fd = open(param[i], O_WRONLY | O_CREAT | O_TRUNC);
		else if (flag_r == 2)
			fd = open(param[i], O_WRONLY | O_CREAT | O_APPEND);
		else if (flag_r == 3)
			fd = open(param[i], O_RDONLY);
		i++;
	}
	close(fd);
}

void	ms_redir(char *param)
{
	int status;
	
	search_redir(param);
	open_files(param);
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (flag == 1)
		else if (flag == 2)
		else if (flag == 3)
		exit();
	}
	wait(&status);
}