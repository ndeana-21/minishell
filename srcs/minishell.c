/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 02:19:30 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/27 17:07:40 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			ms_pipe(param, pip);
		}
		param = (t_dl_list *)param->next;
	}
	return (param);
}

int					is_sep(char *elem, int flag)
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

void				minishell_l(t_dl_list *param, t_pipe *pip, t_redir *redir)
{
	while (param)
	{
		if ((pip->count = find_pipe(param)))
		{
			pipe(pip->fd[0]);
			if (!(pip->pid = fork()))
			{
				dup2(pip->fd[0][STDOUT_FILENO], STDOUT_FILENO);
				shell_brach_red(param, redir);
				exit(g_exit);
			}
			if (pip->pid == -1)
				exit(ft_puterr("minishell: ", NULL, strerror(errno), 1));
			param = shell_branch_sep(param, pip);
		}
		else
			param = shell_brach_red(param, redir);
		param = (t_dl_list *)param->next;
	}
}

void				minishell(char **line)
{
	t_dl_list	*param;
	t_dl_list	*tmp;
	t_pipe		*pip;
	t_redir		*redir;

	param = parsing(*line);
	tmp = param;
	ft_strdel(line);
	if (!param || !(param->content))
		return ;
	if (!(((char *)(param->content))[0]))
	{
		if (param->next)
			param = (t_dl_list *)param->next;
		else
			return ;
	}
	redir = redir_init();
	if (!(pip = pipe_init()))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	minishell_l(param, pip, redir);
	free(pip);
	free(redir);
	ft_dl_lstclear(tmp, free);
}
