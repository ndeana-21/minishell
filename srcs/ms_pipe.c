/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:47:58 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/12 03:17:37 by ndeana           ###   ########.fr       */
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
	char	*param_parent;
	char	*param_child;
	int		fd[2];
	int		child[2];
	int		status[2];

	param_parent = ((char *)ft_dl_lstnnext(param, -1)->content);
	param_child = ((char *)ft_dl_lstnnext(param, 1)->content);
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("An error occured with openning to pipe\n", 1);
		errno = EMFILE;
		return ;
	}
	child[0] = fork();
	pipe_parent(child[0], fd, param_parent);
	child[1] = fork();
	pipe_child(child[1], fd, param_child);
	close(fd[0]);
	close(fd[1]);
	waitpid(child[1], &status[1], 0);
	waitpid(child[0], &status[0], 0);
}
