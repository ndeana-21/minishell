/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 02:19:30 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/26 19:25:10 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_dl_list	*shell_branch_sep(t_dl_list *param, t_pprd *pip)
{
	t_dl_list *tmp;

	tmp = param;
	if (param->next && is_sep(((t_dl_list *)param->next)->content,
		RD_OUT | RD_APP | RD_IN))
	{
		while (param->next)
		{
			if (ft_strsame(param->content, "<"))
			{
				redir->type = 1;
				ms_redir_do(param, redir);
				redir->count -= 1;
			}
			else if (ft_strsame(param->content, ">"))
			{
				redir->type = 2;
				ms_redir(param, redir);
				redir->count -= 1;
			}
			else if (ft_strsame(param->content, ">>"))
			{
				redir->type = 3;
				ms_redir_add(param, redir);
				redir->count -= 1;
			}
			if (is_sep(param->content, PIPE | SEP))
				break ;
			param = (t_dl_list *)param->next;
		}
		run_cmd(tmp->content);
		close(redir->fd);
		dup2(redir->fd_out, STDOUT_FILENO);
		dup2(redir->fd_in, STDIN_FILENO);
		return (param);
	}
	run_cmd(param->content);
	return (param);
}

static t_dl_list	*shell_branch_sep(t_dl_list *param, t_pipe *pip)
{
	while (param)
	{
		if (!(param->next))
			return (param);
		else if (ft_strsame(param->content, ";"))
			return (param);
		else if (ft_strsame(param->content, "|"))
		{
			pip->count -= 1;
			pip->pos += 1;
			ms_pipe(&param, pip);
		}
		param = (t_dl_list *)param->next;
	}
	return (param);
}

int		is_sep(char *elem, int flag)
{
	if ((PIPE == (flag & PIPE)) && ft_strsame("|", elem))
		return (1);
	if ((RD_OUT == (flag & RD_OUT)) && ft_strsame(">", elem))
		return (1);
	if ((RD_IN == (flag & RD_IN)) && ft_strsame("<", elem))
		return (1);
	if ((RD_APP == (flag & RD_APP)) && ft_strsame(">>", elem))
		return (1);
	if ((SEP == (flag & SEP)) && ft_strsame(";", elem))
		return (1);
	return (0);
}

void		minishell_l(t_dl_list *param, t_pipe *pip, t_redir *redir)
{
	while (param)
	{
		if ((pip->count = find_pipe(param)))
		{
			pipe(pprd->fd_pipe[0]);
			if (!(pprd->pid = fork()))
			{
				dup2(pip->fd[0][STDOUT_FILENO], STDOUT_FILENO);
				//run_cmd(param->content);
				shell_brach_red(param, redir);
				exit(g_exit);
			}
			if (pprd->pid == -1)
				exit(ft_puterr(NULL, NULL, strerror(errno), 1));
			param = shell_branch_sep(param, pprd);
		}
		else if (!(is_sep(param->content,
				PIPE | SEP | RD_IN | RD_OUT | RD_APP)))
			param = shell_brach_red(param, redir);
		if (param)
			param = (t_dl_list *)param->next;
	}
}

void		minishell(char **line)
{
	t_dl_list	*param;
	t_dl_list	*tmp;
	t_pipe		*pip;
	t_redir		*redir;

	param = parsing(*line);
	tmp = param;
	ft_strdel(line);
	if (!param)
		return ;
	redir = redir_init();
	redir->fd_in = dup(0);
	redir->fd_out = dup(1);
	if (!(pip = pipe_init()))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	minishell_l(param, pip, redir);
	free(pip);
	ft_dl_lstclear(tmp, free);
}
