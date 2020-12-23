/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:47:58 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/23 20:47:36 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ms_pipe(t_dl_list *param, t_pipe *pip)
{
	if (pip->count)
		if (pipe(pip->fd[(pip->pos) % 2]) == -1)
			return (ft_puterr("minishell: ", NULL, strerror(errno), 1));
	close(pip->fd[1 - (pip->pos) % 2][STDOUT_FILENO]);
	if (!(pip->pid = fork()))
	{
		dup2(pip->fd[1 - ((pip->pos) % 2)][STDIN_FILENO], STDIN_FILENO);
		if (pip->count)
			dup2(pip->fd[(pip->pos) % 2][STDOUT_FILENO], STDOUT_FILENO);
		run_cmd((char *)ft_dl_lstnnext(param, 1)->content);
		exit(g_exit);
	}
	else if (pip->pid == -1)
		return (ft_puterr("minishell: ", NULL, strerror(errno), 1));
	else
	{
		if (!(pip->count))
			waitpid(pip->pid, &pip->status, 0);
		g_exit = pip->status / 256;
		close(pip->fd[1 - (pip->pos) % 2][STDIN_FILENO]);
	}
	return (0);
}
