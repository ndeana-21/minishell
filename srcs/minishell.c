/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:13:19 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/18 20:58:11 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO при $? должен выдаваться номер последней ошибки
//TODO Search and launch the right executable
//TODO echo cd pwd export unset env exit
//TODO ' " ; < > >> | $

int		pipe_handler(t_dl_list *lst)
{
	if (!lst)
		return (0);
	else if (!(ft_strsame((char *)lst->content, "|")))
		return (0);
}

int		append_fd_handler(t_dl_list *lst)
{
	if (!lst)
		return (0);
	else if (!(ft_strsame((char *)lst->content, ">>")))
		return (0);
	
}

int		fd_handler(t_dl_list *lst)
{
	if (!lst)
		return (0);
	else if (!(ft_strsame((char *)lst->content, ">")) &&
			!(ft_strsame((char *)lst->content, "<")))
		return (0);
}

char	*prepare_param(char *param, char *command)
{
	char	*buf;

	buf = ft_strreplace(param, "", 0, ft_strlen(command));
	buf = ft_strpass_rev(buf, " ");
	return (buf);
}

int		check_shell_command(t_dl_list **lst, char *command, void (*func)(char *))
{
	char	*buff;

	if (ft_strlen(command) == ft_strcmp((char *)(*lst)->content, command))
	{
		buff = prepare_param((char *)(*lst)->content, command);
		func(ft_strpass(buff, " "));
		free (buff);
		return (TRUE);
	}
	return (FALSE);
}

void	minishell(char *line)
{
	t_dl_list	*param;

	param = parsing(line);
	while (param)
	{
		if (check_shell_command(&param, MS_ECHO, ms_echo))
			break ;
		///else if (check_shell_command(&param, MS_CD, ms_cd))
			//continue ;
		else if (check_shell_command(&param, MS_PWD, ms_pwd))
			break ;
		//else if (check_shell_command(&param, MS_EXPORT, ms_export))
			//continue ;
		//else if (check_shell_command(&param, MS_UNSET, ms_unset))
			//continue ;
		else if (check_shell_command(&param, MS_ENV, ms_env))
			break ;
		else if (check_shell_command(&param, MS_EXIT, ms_exit))
			break ;
		//else
			//ms_exec(&param);
		param = param->next;
	}
	param = ft_dl_lstclear(param, free);
}

void		init_env(char **env)
{
	t_env	*data;
	size_t	count;

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
