/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:25:18 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/26 20:34:34 by ndeana           ###   ########.fr       */
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
			error_exit(1, "Couldn't open file");
		dup2(redir->fd, fd);
		dup2(fd, 1);
		redir->fd = fd;
		close(fd);
	}
	else
	{
		tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
		if ((fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0744)) < 0)
			error_exit(1, "Couldn't open file");
		dup2(fd, 1);
		redir->fd = fd;
		close(fd);
	}
	g_exit = g_exit / 256;
}

void	ms_redir_add(t_dl_list *param, t_redir *redir)
{
	int		fd;
	char	*tmp;

	if (ft_dl_lstnnext(param, -2) &&
			!(ft_strsame(";", (char *)ft_dl_lstnnext(param, -2)->content)))
	{
		tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
		if ((fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0744) < 0))
			error_exit(1, "Couldn't open file");
		dup2(redir->fd, fd);
		dup2(fd, 1);
		redir->fd = fd;
		close(fd);
	}
	else
	{
		tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
		if ((fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0744)) < 0)
			error_exit(1, "Couldn't open file");
		dup2(fd, 1);
		redir->fd = fd;
		close(fd);
	}
	g_exit = g_exit / 256;
}

void	ms_redir_do(t_dl_list *param, t_redir *redir)
{
	int		fd;
	char	*tmp;

	if (ft_dl_lstnnext(param, -2) &&
			!(ft_strsame(";", (char *)ft_dl_lstnnext(param, -2)->content)))
	{
		tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
		if ((fd = open(tmp, O_RDONLY, 0644) < 0))
			error_exit(1, "Couldn't open file");
		dup2(redir->fd, fd);
		dup2(fd, 0);
		redir->fd = fd;
		close(fd);
	}
	else
	{
		tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
		if ((fd = open(tmp, O_RDONLY, 0644)) < 0)
			error_exit(1, "Couldn't open file");
		dup2(fd, 0);
		redir->fd = fd;
		close(fd);
	}
	g_exit = g_exit / 256;
}
