/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 02:19:30 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/25 23:13:29 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dl_list	*shell_brach_red(t_dl_list *param, t_redir *redir)
{
	t_dl_list *tmp;

	tmp = param;
	if (param->next && is_sep(((t_dl_list *)param->next)->content, RD_OUT | RD_APP | RD_IN))
	{
		while (param->next)
		{	
			if (ft_strsame(param->content, "<"))
       		{
				ms_redir_do(param, redir);
				redir->count -= 1;
				redir->type = 1;
			}
    		else if (ft_strsame(param->content, ">"))
			{
        		ms_redir(param, redir);
				redir->count -= 1;
				redir->type = 2;
			}
    		else if (ft_strsame(param->content, ">>"))
        	{
        		ms_redir_add(param, redir);
				redir->count -= 1;
				redir->type = 3;
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
			ms_pipe(param, pip);
		}
		//else if (ft_strsame(param->content, "<"))
		//   ms_redir(param, O_RDONLY, 0644, 0);
		//else if (ft_strsame(param->content, ">"))
		//    ms_redir(param, O_WRONLY | O_CREAT | O_TRUNC, 0744, 1);
		//else if (ft_strsame(param->content, ">>"))
		//    ms_redir(param, O_WRONLY | O_CREAT | O_APPEND, 0744, 1);
		param = (t_dl_list *)param->next;
	}
	return (param);
}

void	shell_brach_ut(t_dl_list *param)
{
	t_dl_list *tmp;

	tmp = param;
	while (tmp)
	{	
		if (ft_strsame(tmp->content, "<"))
       		dup2(0, 1);
    	else if (ft_strsame(tmp->content, ">"))
        	dup2(1, 0);
    	else if (ft_strsame(tmp->content, ">>"))
        	dup2(1, 0);
    	tmp = (t_dl_list *)tmp->next;
	}
}

t_pipe	*pipe_init(void)
{
	t_pipe	*pipe;

	if (!(pipe = ft_calloc(sizeof(t_pipe), 1)))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	pipe->count = 0;
	pipe->pos = 0;
	pipe->pid = -1;
	pipe->fd[0][0] = -1;
	pipe->fd[0][1] = -1;
	pipe->fd[1][0] = -1;
	pipe->fd[1][1] = -1;
	return (pipe);
}

t_redir	*redir_init(void)
{
	t_redir	*redir;

	if (!(redir = ft_calloc(sizeof(t_redir), 1)))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	redir->count = 0;
	redir->fd_in = STDIN_FILENO;
	redir->fd_out = STDOUT_FILENO;
	redir->type = 0;
	redir->fd = -1;
	return (redir);
}

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
int		find_pipe(t_dl_list *param)
{
	int	count;

	count = 0;
	while (param->next && !(ft_strsame(";", param->content)))
	{
		if (ft_strsame("|", param->content))
			count++;
		param = (t_dl_list *)param->next;
	}
	return (count);
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

void	minishell(char **line)
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
	while (param)
	{
		//if ((redir->count = find_redir(param)))
		//{
		//	shell_brach_red(param, redir);
		//}
		if ((pip->count = find_pipe(param)))
		{
			pipe(pip->fd[0]);
			if (!(pip->pid = fork()))
			{
				dup2(pip->fd[0][STDOUT_FILENO], STDOUT_FILENO);
				run_cmd(param->content);
				exit(g_exit);
			}
			if (pip->pid == -1)
				exit(ft_puterr("minishell: ", NULL, strerror(errno), 1));
			param = shell_branch_sep(param, pip);
		}
		else
			if (!(is_sep(param->content, PIPE | SEP | RD_IN | RD_OUT | RD_APP)))
				param = shell_brach_red(param,redir);	
		if (param)
			param = (t_dl_list *)param->next;
	}
	free(pip);
	ft_dl_lstclear(tmp, free);
}
