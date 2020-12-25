/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 02:19:30 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/26 00:43:43 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_dl_list	*shell_branch_sep(t_dl_list *param, t_pprd *pip)
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

t_pprd	*pprd_init(void)
{
	t_pprd	*pprd;

	if (!(pprd = ft_calloc(sizeof(t_pprd), 1)))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	pprd->count = 0;
	pprd->pos = 0;
	pprd->pid = -1;
	pprd->fd_pipe[0][0] = -1;
	pprd->fd_pipe[0][1] = -1;
	pprd->fd_pipe[1][0] = -1;
	pprd->fd_pipe[1][1] = -1;
	pprd->fd_in = dup(STDIN_FILENO);
	pprd->fd_out = dup(STDOUT_FILENO);
	return (pprd);
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
		else
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
	t_pprd		*pprd;
	
	param = parsing(*line);
	tmp = param;
	ft_strdel(line);
	if (!param)
		return ;
	if (!(pprd = pprd_init()))
		error_exit(EXIT_FAILURE, ERROR_MALLOC);
	while (param)
	{
		if ((pprd->count = find_pipe(param)))
		{
			pipe(pprd->fd_pipe[0]);
			if (!(pprd->pid = fork()))
			{
				dup2(pprd->fd_pipe[0][STDOUT_FILENO], STDOUT_FILENO);
				param = shell_brach_red(param, pprd);
				exit(g_exit);
			}
			if (pprd->pid == -1)
				exit(ft_puterr(NULL, NULL, strerror(errno), 1));
			param = shell_branch_sep(param, pprd);
		}
		else
			if (!(is_sep(param->content, SEP | PIPE)))
				param = shell_brach_red(param, pprd);
		if (param)
			param = (t_dl_list *)param->next;
	}
	free(pprd);
	ft_dl_lstclear(tmp, free);
}
