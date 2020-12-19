/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:25:18 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/19 22:00:33 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_redir(t_dl_list *param, int perm, int descr, int to_dup, int *fd_count)
{
	//int		fd;
	char	*tmp;
	static int	fd[2][2];
	//char	*tmp_p;
	pid_t	pid;
	int i = 0;
	//t_dl_list	*buf_lst;


	tmp = ((char *)ft_dl_lstnnext(param, 1)->content);
	//tmp_p = ((char *)ft_dl_lstnnext(param, -1)->content);
	if (ft_strsame(">", (char *)(t_dl_list *)param->content))
	{
		i++;
		param = (t_dl_list *)param->next;
	}
	if ((fd[0][1] = open(tmp, perm, descr)) < 0)
		write(1, "Couldn't open file\n", 19);
	while (param)
	{
		if (!(pid = fork()))
		{
			if ((fd[0][2] = open(tmp, perm, descr)) < 0)
				write(1, "Couldn't open file\n", 19);
			dup2(fd[0][2], fd[1][0]);
			dup2(fd[1][0],to_dup);
			close(fd[0][2]);
			close(fd[1][0]);
			//shell_brach_cmd(tmp_p);
			exit(EXIT_SUCCESS);
		}
			//if (buf_lst = ft_dl_lstnnext(param, 2))
			//{
			//	if (!(pid = fork()))
			//	{
			//		dup2(fd, to_dup);
			//		close(fd);
			//		//shell_brach_cmd(tmp_p);
			//		exit(EXIT_SUCCESS);
			//	}
			//}
		param = (t_dl_list *)param->next;
	}
	//free(tmp);
	//free(tmp_p);
	wait(&g_exit);
	g_exit = g_exit / 256;
}

void	ms_redir_do(t_dl_list *param, int perm, int descr, int to_dup)
{
	int		fd;
	char	*tmp;
	char	*tmp_p;
	pid_t	pid;
	//t_dl_list	*buf_lst;

	tmp = ((char *)ft_dl_lstnnext(param, -1)->content);
	tmp_p = ((char *)ft_dl_lstnnext(param, 1)->content);
	if ((fd = open(tmp_p, perm, descr)) < 0)
		write(1, "Couldn't open file\n", 19);
	if ((ft_dl_lstnnext(param, 2)) || ft_strsame(";", (char *)ft_dl_lstnnext(param, 2)->content))
	{
		if (!(pid = fork()))
		{
			dup2(fd, to_dup);
			close(fd);
			shell_brach_cmd(tmp);
			exit(EXIT_SUCCESS);
		}
	}
	//free(tmp);
	//free(tmp_p);
	wait(&g_exit);
	g_exit = g_exit / 256;
}
