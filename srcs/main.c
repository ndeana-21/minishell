/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 03:35:29 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/11 17:28:48 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO exit "
//TODO cd ~/ SEGA

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
	#if 0
	if (argv[1][0] == '-' && argv[1][1] == 'c')
	{
		char *tmp = ft_strdup(argv[2]);
		ms_dollar(&tmp);
		minishell(&tmp);	
	}
	else
	#endif
	{
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
	}
	exit(0);
}
