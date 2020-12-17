/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:47:58 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/17 21:05:12 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		pipe_parent(int child, int fd[2], char *param)
{
	if (child == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		shell_brach_cmd(param);
		exit(EXIT_SUCCESS);
	}
}

void		pipe_child(int child, int fd[2], char *param)
{
	if (child == 0)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		shell_brach_cmd(param);
		exit(EXIT_SUCCESS);
	}
}

void		ms_pipe(t_dl_list *param)
{
	t_dl_list	*buf_lst;
	int			fd[2];
	pid_t		child[2];
	int			status[2];

	if (pipe(fd) == -1)
	{
		ft_putstr_fd("An error occured with openning to pipe\n", 1);
		errno = EMFILE;
		return ;
	}
	if (!(ft_dl_lstnnext(param, -2)) ||
		ft_strsame(";", (char *)ft_dl_lstnnext(param, -2)->content))
	{
		if (!(child[0] = fork()))
		{
			pipe_parent(child[0], fd, (char *)(ft_dl_lstnnext(param, -1)->content));
			close(fd[0]);
			waitpid(child[0], &status[0], WNOHANG);
			exit(status[0]);
		}
	}
	else
	{
		child[0] = g_child;
		fd[0] = g_fd;
	}
	if (!(child[1] = fork()))
		pipe_child(child[1], fd, (char *)(ft_dl_lstnnext(param, 1)->content));
	close(fd[1]);
	if (!(buf_lst = ft_dl_lstnnext(param, 2)) ||
		ft_strsame(";", (char *)(buf_lst->content)))
	{
		waitpid(child[1], &status[1], 0);
		exit(status[1]);
	}
	g_fd = fd[1];
	g_child = child[1];
}
/*
void		ms_pipe(t_dl_list *param)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	char	*param_parent;
	char	*param_child;

	printf("%s", (char *)ft_dl_lstnnext(param, 0)->content);
	param_parent = ((char *)ft_dl_lstnnext(param, -1)->content);
	param_child = ((char *)ft_dl_lstnnext(param, 1)->content);
	//if (pipe(fd) == -1)
	//	ft_putstr_fd("An error occured with openning to pipe\n", 1);
	//	errno = EMFILE;
	//	return ;
	if ((pid = fork()) == -1)
		return ;
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		shell_brach_cmd(param_parent);
		exit(0);
	}
	else
	{
		if (waitpid(pid, &status, 0) != pid)
			return ;
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		if (shell_branch_sep(param) == 2)
		{
			param = param->next;
			ms_pipe(param);
		}
		shell_brach_cmd(param_child);
	}
}
*/