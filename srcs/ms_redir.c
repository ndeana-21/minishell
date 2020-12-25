/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:25:18 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/26 00:39:41 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_redir(t_dl_list *param, t_pprd *redir)
{
	int		fd;
	char	*tmp;

	if (ft_dl_lstnnext(param, -2) &&
			!(ft_strsame(";", (char *)ft_dl_lstnnext(param, -2)->content)))
	{
		tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
		if ((fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0744) < 0))
			write(1, "Couldn't open file\n", 19);
		dup2(redir->fd_rd, fd);
		dup2(fd, 1);
		redir->fd_rd = fd;
		close(fd);
	}
	else
	{
		tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
		if ((fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0744)) < 0)
			write(1, "Couldn't open file\n", 19);
		if (redir->fd_rd != -1)
			dup2(redir->fd_rd, fd);
		else
			dup2(fd, 1);
		redir->fd_rd = fd;
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
			write(1, "Couldn't open file\n", 19);
		dup2(redir->fd_rd, fd);
		dup2(fd, 1);
		redir->fd_rd = fd;
		close(fd);
	}
	else
	{
		tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
		if ((fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0744)) < 0)
			write(1, "Couldn't open file\n", 19);
		if (redir->fd_rd != -1)
			dup2(redir->fd_rd, fd);
		else
			dup2(fd, 1);
		redir->fd_rd = fd;
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
		if ((fd = open(tmp,  O_RDONLY, 0644) < 0))
			write(1, "Couldn't open file\n", 19);
		dup2(redir->fd_rd, fd);
		dup2(fd, 0);
		redir->fd_rd = fd;
		close(fd);
	}
	else
	{
		tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
		if ((fd = open(tmp, O_RDONLY, 0644)) < 0)
			write(1, "Couldn't open file\n", 19);
		dup2(fd, 0);
		redir->fd_rd = fd;
		close(fd);
	}
	free(tmp);
	g_exit = g_exit / 256;
}

t_dl_list	*shell_brach_red(t_dl_list *param, t_pprd *redir)
{
	t_dl_list *tmp;

	tmp = param;
	if (param->next && is_sep(((t_dl_list *)param->next)->content, RD_OUT | RD_APP | RD_IN))
	{
		while (param->next)
		{	
			if (is_sep(tmp->content, RD_IN))
				ms_redir_do(param, redir);
    		else if (is_sep(tmp->content, RD_OUT))
        		ms_redir(param, redir);
    		else if (is_sep(tmp->content, RD_APP))
        		ms_redir_add(param, redir);
			else if (is_sep(param->content, PIPE | SEP))
				break ;
			param = (t_dl_list *)param->next;
		}
		if (!(is_sep(tmp->content, 011111)))
			run_cmd(tmp->content);
		close(redir->fd_rd);
		dup2(redir->fd_out, STDOUT_FILENO);
		dup2(redir->fd_in, STDIN_FILENO);
		return (param);
	}
	run_cmd(param->content);
	return (param);
}
