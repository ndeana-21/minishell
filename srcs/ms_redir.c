/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:25:18 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/26 18:44:35 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_redir(t_dl_list *param)
{
	int	count;

	count = 0;
	while (param->next && !(ft_strsame(";", param->content)))
	{
		if (ft_strsame(param->content, "<"))
			count++;
		else if (ft_strsame(param->content, ">"))
			count++;
		else if (ft_strsame(param->content, ">>"))
			count++;
		param = (t_dl_list *)param->next;
	}
	return (count);
}

void	ms_redir(t_dl_list *param, t_redir *redir)
{
	int		fd;
	char	*tmp;

	if (ft_dl_lstnnext(param, -2) &&
			!(ft_strsame(";", (char *)ft_dl_lstnnext(param, -2)->content)))
	{
		tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
		if ((fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0744) < 0))
			print_error(2, "Couldn't open file\n");
		dup2(redir->fd, fd);
		dup2(fd, 1);
		redir->fd_rd = fd;
		close(fd);
	}
	else
	{
		tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
		if ((fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0744)) < 0)
			print_error(2, "Couldn't open file\n");
		dup2(fd, 1);
		redir->fd = fd;
		close(fd);
	}
	free(tmp);
	g_exit = g_exit / 256;
}

static void	ms_redir_add(t_dl_list *param, t_pprd *redir)
{
	int		fd;
	char	*tmp;

	if (ft_dl_lstnnext(param, -2) &&
			!(ft_strsame(";", (char *)ft_dl_lstnnext(param, -2)->content)))
	{
		tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
		if ((fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0744) < 0))
			print_error(2, "Couldn't open file\n");
		dup2(redir->fd, fd);
		dup2(fd, 1);
		redir->fd_rd = fd;
		close(fd);
	}
	else
	{
		tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
		if ((fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0744)) < 0)
			print_error(2, "Couldn't open file\n");
		dup2(fd, 1);
		redir->fd = fd;
		close(fd);
	}
	free(tmp);
	g_exit = g_exit / 256;
}

static void	ms_redir_do(t_dl_list *param, t_pprd *redir)
{
	int		fd;
	char	*tmp;

	if (ft_dl_lstnnext(param, -2) &&
			!(ft_strsame(";", (char *)ft_dl_lstnnext(param, -2)->content)))
	{
		tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
		if ((fd = open(tmp, O_RDONLY, 0644) < 0))
			print_error(2, "Couldn't open file\n");
		dup2(redir->fd, fd);
		dup2(fd, 0);
		redir->fd_rd = fd;
		close(fd);
	}
	else
	{
		tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
		if ((fd = open(tmp, O_RDONLY, 0644)) < 0)
			print_error(2, "Couldn't open file\n");
		dup2(fd, 0);
		redir->fd_rd = fd;
		close(fd);
	}
	//free(tmp);
	g_exit = g_exit / 256;
}
