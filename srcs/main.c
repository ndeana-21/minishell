/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 03:35:29 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/10 16:26:25 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO exit "
//TODO cd ~/ SEGA

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
		shell_brach_command(tmp_p);
		exit(EXIT_SUCCESS);
	}
	free(tmp);
	free(tmp_p);
	wait(&g_exit);
	g_exit = g_exit / 256;
}

void	deal_with_input(char **line)
{
	char	*readout;
	char	*tmp;

	readout = NULL;
	tmp = NULL;
	if (0 > (ft_read_fd(0, &readout)))
		ft_putendl_fd(ERROR_READ, 2);
	if (!(*line) && !(readout))
		ms_exit(NULL);
	if (!(*line) || !(readout))
	{
		if (!(*line))
			*line = readout;
		return ;
	}
	if (!(tmp = ft_strjoin(*line, readout)))
		error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
	ft_strdel(&readout);
	ft_strdel(line);
	*line = tmp;
}

int		main(int argc, char **argv, char **env)
{
	char	*line;

	(void)argc;
	g_name = argv[0];
	init_env(env);
	set_signal();
	line = NULL;
	while (TRUE)
	{
		if (!(line))
			prompt();
		deal_with_input(&line);
		if (line[ft_strlen(line) - 1] == '\n')
		{
			line[ft_strlen(line) - 1] = 0;
			if (!(*line))
			{
				ft_strdel(&line);
				continue ;
			}
			ms_dollar(&line);
			minishell(&line);
		}
	}
	exit(0);
}
