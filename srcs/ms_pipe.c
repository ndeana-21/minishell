/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:47:58 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/11 12:29:12 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		pipe_parent(int child, int fd[2], char **param)
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

void		pipe_child(int child[2], int fd[2], char **param)
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
	int		i;
	char	**param_parent;
	int		fd[2];
	int		child[2];
	int		status[2];

	i = 0;
	param_parent = ((char *)ft_dl_lstnnext(param, -1)->content);
	param = ((char *)ft_dl_lstnnext(param, 1)->content);
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("An error occured with openning to pipe\n", 1);
		errno = EMFILE;
		return ;
	}
	child[0] = fork();
	pipe_parent(child[0], fd, param_parent);
	child[1] = fork();
	pipe_child(child[1], fd, param);
	close(fd[0]);
	close(fd[1]);
	waitpid(child[1], &status[1], 0);
	waitpid(child[0], &status[0], 0);
}
