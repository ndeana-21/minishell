/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:25:18 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/27 17:11:27 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			ms_redir(t_dl_list *param, t_redir *redir)
{
	int		fd;

	if (ft_dl_lstnnext(param, -2) &&
			!(ft_strsame(";", (char *)ft_dl_lstnnext(param, -2)->content)))
	{
		if ((fd = open(ft_strpass_rev((char *)ft_dl_lstnnext(param, 1)->content,
				" "), O_WRONLY | O_CREAT | O_TRUNC, 0744) < 0))
			error_exit(1, "Couldn't open file");
		dup2(redir->fd, fd);
		dup2(fd, 1);
		redir->fd = fd;
		close(fd);
	}
	else
	{
		if ((fd = open(ft_strpass_rev((char *)ft_dl_lstnnext(param, 1)->content,
				" "), O_WRONLY | O_CREAT | O_TRUNC, 0744)) < 0)
			error_exit(1, "Couldn't open file");
		dup2(fd, 1);
		redir->fd = fd;
		close(fd);
	}
	g_exit = g_exit / 256;
}

static void			ms_redir_add(t_dl_list *param, t_redir *redir)
{
	int		fd;

	if (ft_dl_lstnnext(param, -2) &&
			!(ft_strsame(";", (char *)ft_dl_lstnnext(param, -2)->content)))
	{
		if ((fd = open(ft_strpass_rev((char *)ft_dl_lstnnext(param, 1)->content,
				" "), O_WRONLY | O_CREAT | O_APPEND, 0744) < 0))
			error_exit(1, "Couldn't open file");
		dup2(redir->fd, fd);
		dup2(fd, 1);
		redir->fd = fd;
		close(fd);
	}
	else
	{
		if ((fd = open(ft_strpass_rev((char *)ft_dl_lstnnext(param, 1)->content,
				" "), O_WRONLY | O_CREAT | O_APPEND, 0744)) < 0)
			error_exit(1, "Couldn't open file");
		dup2(fd, 1);
		redir->fd = fd;
		close(fd);
	}
	g_exit = g_exit / 256;
}

static void			ms_redir_do(t_dl_list *param, t_redir *redir)
{
	int		fd;

	if (ft_dl_lstnnext(param, -2) &&
			!(ft_strsame(";", (char *)ft_dl_lstnnext(param, -2)->content)))
	{
		if ((fd = open(ft_strpass_rev((char *)ft_dl_lstnnext(param, 1)->content,
				" "), O_RDONLY, 0644) < 0))
			error_exit(1, "Couldn't open file");
		dup2(redir->fd, fd);
		dup2(fd, 0);
		redir->fd = fd;
	}
	else
	{
		if ((fd = open(ft_strpass_rev((char *)ft_dl_lstnnext(param, 1)->content,
				" "), O_RDONLY, 0644)) < 0)
			error_exit(1, "Couldn't open file");
		dup2(fd, 0);
		redir->fd = fd;
		close(fd);
	}
	g_exit = g_exit / 256;
}

static t_dl_list	*shell_brach_red_util(t_dl_list *param, t_redir *redir)
{
	while (param->next)
	{
		if (ft_strsame(param->content, "<"))
			ms_redir_do(param, redir);
		else if (ft_strsame(param->content, ">"))
			ms_redir(param, redir);
		else if (ft_strsame(param->content, ">>"))
			ms_redir_add(param, redir);
		if (is_sep(param->content, PIPE | SEP))
			break ;
		param = (t_dl_list *)param->next;
	}
	return (param);
}

t_dl_list			*shell_brach_red(t_dl_list *param, t_redir *redir)
{
	t_dl_list *tmp;

	tmp = param;
	if (param->next && (is_sep(param->content, 001110) ||
						is_sep(((t_dl_list *)param->next)->content, 001110)))
	{
		param = shell_brach_red_util(param, redir);
		if (!is_sep(tmp->content, 011111))
			run_cmd(tmp->content);
		close(redir->fd);
		dup2(redir->fd_out, STDOUT_FILENO);
		dup2(redir->fd_in, STDIN_FILENO);
		return (param);
	}
	if (!is_sep(tmp->content, 011111))
		run_cmd(tmp->content);
	return (param);
}
