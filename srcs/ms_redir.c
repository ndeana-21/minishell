/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:25:18 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/17 21:02:02 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_redir(t_dl_list *param, int perm, int descr, int to_dup)
{
	int		fd;
	char	*tmp;
	char	*tmp_p;
	pid_t	pid;

	tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
	tmp_p = ((char *)ft_dl_lstnnext(param, -1)->content);
	if ((fd = open(tmp, perm, descr)) < 0)
		write(1, "Couldn't open file\n", 19);
	if (!(pid = fork()))
	{
		dup2(fd, to_dup);
		close(fd);
		shell_brach_cmd(tmp_p);
		exit(EXIT_SUCCESS);
	}
	free(tmp);
	free(tmp_p);
	wait(&g_exit);
	g_exit = g_exit / 256;
}
