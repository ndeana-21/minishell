/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 02:19:30 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/23 01:02:04 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_brach_red(t_dl_list *param)
{
	t_dl_list *tmp;

	tmp = param;
	while (tmp)
	{	
		if (ft_strsame(tmp->content, "<"))
       		ms_redir(tmp, O_RDONLY, 0644, 0);
    	else if (ft_strsame(tmp->content, ">"))
        	ms_redir(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0744, 1);
    	else if (ft_strsame(tmp->content, ">>"))
        	ms_redir(tmp, O_WRONLY | O_CREAT | O_APPEND, 0744, 1);
    	tmp = (t_dl_list *)tmp->next;
	}
}

static t_dl_list	*shell_branch_sep(t_dl_list *param, t_pipe *pip)
{
	while (param)
	{
		if (!(param->next))
			return (param);
		else if (ft_strsame(param->content, ";"))
			return ((t_dl_list *)param->next);
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
       		dup2(1, 0);
    	else if (ft_strsame(tmp->content, ">"))
        	dup2(0, 1);
    	else if (ft_strsame(tmp->content, ">>"))
        	dup2(0, 1);
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

int		is_sep(char *elem)
{
	if (ft_strsame("<", elem) || ft_strsame("<<", elem) ||
		ft_strsame(">", elem) || ft_strsame("|", elem) ||
		ft_strsame(";", elem))
		return (1);
	return (0);
}

void	minishell(char **line)
{
	t_dl_list	*param;
	t_pipe		*pip;
	
	param = parsing(*line);
	ft_strdel(line);
	if (!param)
		return ;
	pip = pipe_init();
	shell_brach_red(param);
	while (param)
	{
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
				exit (ft_puterr("minishell: ", NULL, strerror(errno), 1));
		}
		else
			if (!(is_sep(param->content)))
				run_cmd(param->content);
		if (!(param->next))
			break ;
		param = shell_branch_sep((t_dl_list *)param->next, pip);
		if (!(param->next))
				break ;
	}
	free(pip);
	ft_dl_lstclear(param, free);
}
