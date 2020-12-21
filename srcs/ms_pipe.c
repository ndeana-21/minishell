/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:47:58 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/22 00:09:27 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ms_pipe(t_dl_list *param, int *fd_count)
{
	pid_t		pid;
	int			status;

	*fd_count += 1;
	if (pipe(g_fd[(*fd_count) % 2]) == -1)
	{
		ft_puterr("minishell: ", NULL, strerror(errno), 1);
		return ;
	}
	if (!(pid = fork()))
	{
		dup2(g_fd[(*fd_count) % 2][STDOUT_FILENO], STDOUT_FILENO);
		if (ft_dl_lstnnext(param, -2) &&
			!(ft_strsame(";", (char *)ft_dl_lstnnext(param, -2)->content)))
			dup2(g_fd[1 - (*fd_count) % 2][STDIN_FILENO], STDIN_FILENO);
		run_cmd((char *)ft_dl_lstnnext(param, 1)->content);
		exit(g_exit);
	}
	else if (pid == -1)
	{
		ft_puterr("minishell: ", NULL, strerror(errno), 1);
		return ;
	}
	else
	{
		waitpid(pid, &status, 0);
		printf("here\n");
		g_exit = status / 256;
		close(g_fd[(*fd_count) % 2][STDOUT_FILENO]);
		if (!(ft_dl_lstnnext(param, 2)) ||
			(ft_strsame(";", (char *)ft_dl_lstnnext(param, 2)->content)))
			close(g_fd[(*fd_count) % 2][STDIN_FILENO]);
		if (ft_dl_lstnnext(param, -2) &&
			!(ft_strsame(";", (char *)ft_dl_lstnnext(param, -2)->content)))
			close(g_fd[1 - (*fd_count) % 2][STDIN_FILENO]);
	}
	




	// if (!(ft_dl_lstnnext(param, -2)) ||
	// 	ft_strsame(";", (char *)ft_dl_lstnnext(param, -2)->content))
	// {
	// 	if (!(pid = fork()))
	// 		pipe_child(g_fd[(*fd_count) % 2][STDIN_FILENO], STDIN_FILENO,
	// 					(char *)(ft_dl_lstnnext(param, 1)->content));
	// 	dup2(STDOUT_FILENO, g_fd[(*fd_count) % 2][STDIN_FILENO]);
	// }
	// else
	// 	if (!(pid = fork()))
	// 	{
	// 		pipe_child(g_fd[1 - ((*fd_count) % 2)][STDIN_FILENO], STDIN_FILENO,
	// 					(char *)(ft_dl_lstnnext(param, 1)->content));
	// 		close(g_fd[1 - ((*fd_count) % 2)][STDIN_FILENO]);
	// 	}
	// close(g_fd[(*fd_count) % 2][STDOUT_FILENO]);
	// if (!(ft_dl_lstnnext(param, 2)) ||
	// 	ft_strsame(";", (char *)ft_dl_lstnnext(param, 2)->content))
	// {
	// 	waitpid(pid[0], &status, 0);
	// 	close(g_fd[(*fd_count) % 2][STDIN_FILENO]);
	// 	g_exit = status / 256;
	// }
}
