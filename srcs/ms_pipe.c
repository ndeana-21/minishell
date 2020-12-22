/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:47:58 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/22 20:31:14 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ms_pipe(t_dl_list *param, t_pipe *pip)
{
	int			status;
	pid_t		pid;

	if (pip->count)
		if (pipe(pip->fd[(pip->pos) % 2]) == -1)
			return (ft_puterr("minishell: ", NULL, strerror(errno), 1));
	close(pip->fd[1 - (pip->pos) % 2][STDOUT_FILENO]);
	if (!(pid = fork()))
	{
		dup2(pip->fd[1 - ((pip->pos) % 2)][STDIN_FILENO], STDIN_FILENO);
		if (pip->count)
			dup2(pip->fd[(pip->pos) % 2][STDOUT_FILENO], STDOUT_FILENO);
		run_cmd((char *)ft_dl_lstnnext(param, 1)->content);
		exit(g_exit);
	}
	else if (pid == -1)
		return (ft_puterr("minishell: ", NULL, strerror(errno), 1));
	else
	{
		if (!(pip->count))
			waitpid(pid, &status, 0);
		g_exit = status / 256;
		close(pip->fd[1 - (pip->pos) % 2][STDIN_FILENO]);
	}
	return (0);
}
