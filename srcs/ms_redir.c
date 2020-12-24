/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:25:18 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/24 17:16:01 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_redir(t_dl_list *param, t_redir *redir)
{
	int		fd;
	char	*tmp;

	if (ft_dl_lstnnext(param, -2) &&
			!(ft_strsame(";", (char *)ft_dl_lstnnext(param, -2)->content)))
	{
		tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
		if ((fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0744) < 0))
			write(1, "Couldn't open file\n", 19);
		//dup2(1, fd);
		if (redir->fd != -1)
			dup2(fd, redir->fd);
		else
			dup2(fd, 1);
		redir->fd = fd;
		close(fd);
	}
	else
	{
		tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
		if ((fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0744)) < 0)
			write(1, "Couldn't open file\n", 19);
		if (redir->fd != -1)
			dup2(fd, redir->fd);
		else
			dup2(fd, 1);
		redir->fd = fd;
		//close(fd);
	}
	//free(tmp);
	//wait(&g_exit);
	g_exit = g_exit / 256;
}
/*
void	ms_redir(t_dl_list *param, int perm, int descr, int to_dup)
{
	int		fd;
	char	*tmp;

	if (ft_dl_lstnnext(param, -2) &&
			!(ft_strsame(";", (char *)ft_dl_lstnnext(param, -2)->content)))
	{
		{
			tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
			if ((fd = open(tmp, perm, descr)) < 0)
				write(1, "Couldn't open file\n", 19);
			dup2(fd, to_dup);
			close(fd);
		}
	}
	else
	{
		tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
		if ((fd = open(tmp, perm, descr)) < 0)
			write(1, "Couldn't open file\n", 19);
			dup2(fd, to_dup);
			close(fd);
		}
	//free(tmp);
	//wait(&g_exit);
	g_exit = g_exit / 256;
}

void	ms_redir_do(t_dl_list *param, int perm, int descr, int to_dup)
{
	int		fd;
	char	*tmp;

	if (ft_dl_lstnnext(param, -2) &&
			!(ft_strsame(";", (char *)ft_dl_lstnnext(param, -2)->content)))
	{
		{
			tmp = ((char *)ft_dl_lstnnext(param, -1)->content);
			if ((fd = open(tmp, perm, descr)) < 0)
				write(1, "Couldn't open file\n", 19);
			dup2(fd, to_dup);
			close(fd);
		}
	}
	else
	{
		tmp = ((char *)ft_dl_lstnnext(param, -1)->content);
		if ((fd = open(tmp, perm, descr)) < 0)
			write(1, "Couldn't open file\n", 19);
		dup2(fd, to_dup);
		close(fd);
	}
	//free(tmp);
	wait(&g_exit);
	g_exit = g_exit / 256;
}
*/
