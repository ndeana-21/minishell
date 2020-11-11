/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:13:19 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/11 20:05:12 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO при $? должен выдаваться номер последней ошибки
//TODO Search and launch the right executable
//TODO echo cd pwd export unset env exit
//TODO ' " ; < > >> | $

char	*prepare_param(char *param, char *command)
{
	char	*buf;


}

int		check_shell_command(t_dl_list **lst, char *command, void (*func)(char *))
{
	char	*buff;

	if (ft_strlen(command) == ft_strcmp((char *)(*lst)->content, command))
	{
		buff = prepare_param((char *)(*lst)->content, command);
		func(buff);
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
			continue ;
		else if (check_shell_command(&param, MS_CD, ms_cd))
			continue ;
		else if (check_shell_command(&param, MS_PWD, ms_pwd))
			continue ;
		else if (check_shell_command(&param, MS_EXPORT, ms_export))
			continue ;
		else if (check_shell_command(&param, MS_UNSET, ms_unset))
			continue ;
		else if (check_shell_command(&param, MS_ENV, ms_env))
			continue ;
		else if (check_shell_command(&param, MS_EXIT, ms_exit))
			continue ;
		else
			ms_exec(&param);
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
		if (!(data = malloc(sizeof(t_env))))
			error_exit(ERROR_NUM_MALLOC, ERROR_MALLOC);
		count = -1;
		while ((*env)[++count])
			if (ft_strchr("=", (*env)[count]))
			{
				data->val = &((*env)[count + 1]);
				(*env)[count] = 0;
				data->name = *env;
				break ;
			}
		ft_dl_lstadd_back(&g_envlst, ft_dl_lstnew(data));
		data = 0;
		env++;
	}
}

int			main(int argc, char **argv, char **env)
{
	char	*line;

	(void)argc;
	g_name = argv[0];
	g_envlst = NULL;
	init_env(env);
	// FIXME debug env
	// while (g_envlst)
	// {
	// 	printf("%s=%s\n", ((t_env *)g_envlst->content)->name, ((t_env *)g_envlst->content)->val);
	// 	g_envlst = g_envlst->next;
	// }
	printf("%s\n", line);
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
