/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:13:19 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/22 12:00:30 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO Search and launch the right executable
//TODO cd pwd export unset exit
//TODO ' " ; < > >> | $

// int		pipe_handler(t_dl_list *lst)
// {
// 	return (0);
// }

// int		append_fd_handler(t_dl_list *lst)
// {
// 	return (0);
// }

// int		fd_handler(t_dl_list *lst)
// {
// 	return (0);
// }

char	*prepare_param(char *param, char *command)
{
	char	*buf;

	buf = ft_strreplace(param, "", 0, ft_strlen(command));
	buf = ft_strpass_rev(buf, " ");
	return (buf);
}

int		check_shell_command(char *content, char *command, void (*func)(char *))
{
	char	*buff;

	if (ft_strlen(command) == (size_t)ft_strcmp_reg(content, command))
	{
		buff = prepare_param(content, command);
		func(ft_strpass(buff, " "));
		free (buff);
		return (TRUE);
	}
	return (FALSE);
}

void	shell_brach_command(char *content)
{
	if (check_shell_command(content, MS_ECHO, ms_echo))
		return ;
	// else if (check_shell_command(content, MS_CD, ms_cd))
	// 	return ;
	else if (check_shell_command(content, MS_PWD, ms_pwd))
		return ;
	// else if (check_shell_command(content, MS_EXPORT, ms_export))
	// 	return ;
	// else if (check_shell_command(content, MS_UNSET, ms_unset))
	// 	return ;
	else if (check_shell_command(content, MS_ENV, ms_env))
		return ;
	else if (check_shell_command(content, MS_EXIT, ms_exit))
		return ;
	// else
	// 	ms_exec(content);
	return ;
}

// void	shell_brach_sep(t_dl_list *param)
// {
	
// }

void	minishell(char *line)
{
	t_dl_list	*param;

	ft_strdel(g_ret);
	param = parsing(line);
	while (param)
	{
		printf ("|%s|\n", (char *)param->content);
		shell_brach_command((char *)param->content);
		param = (t_dl_list *)param->next;
	}
	param = ft_dl_lstclear(param, free);
}

void		init_env(char **env)
{
	t_env	*data;
	// size_t	count;

	if (!env)
		return ;
		// error_exit(ERROR_NUM_ENV, ERROR_ENV); FIXME нужно ли?
	while (*env)
	{
		data = create_env(*env);
		ft_dl_lstadd_back(&g_envlst, ft_dl_lstnew(data));
		data = 0;
		env++;
	}
}

int			main(int argc, char **argv, char **env)
{
	char	*line;

	(void)argc;
	g_exit = 0;
	g_name = argv[0];
	g_envlst = NULL;
	g_ret = NULL;
	init_env(env);
	set_signal();
	while (TRUE)
	{
		promt();
		line = NULL;
		if (0 > (ft_read_fd(0, &line)))
			ft_putendl_fd(ERROR_READ, 2);
		else
		{
			if (ft_strlen(line))
				line[ft_strlen(line) - 1] = 0;
			minishell(line);
		}
		free(line);
	}
	return (0);
}
