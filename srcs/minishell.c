/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:13:19 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/06 18:35:41 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO Search and launch the right executable
//TODO cd exit
//TODO ' " ; < > >> |

int		check_shell_command(char *content, char *command, void (*func)(char *))
{
	char	*buff;

	if (ft_strlen(command) == (size_t)ft_strcmp_reg(content, command))
	{
		buff = ft_strreplace(content, "", 0, ft_strlen(command));
		buff = ft_strpass_rev(buff, " ");
		func(ft_strpass(buff, " "));
		free (buff);
		return (TRUE);
	}
	return (FALSE);
}

void	shell_brach_command(char *content)
{
	//printf("%s", "HERO");
	if (check_shell_command(content, MS_ECHO, ms_echo))
		return ;
	else if (check_shell_command(content, MS_CD, ms_cd))
		return ;
	else if (check_shell_command(content, MS_PWD, ms_pwd))
		return ;
	else if (check_shell_command(content, MS_EXPORT, ms_export))
		return ;
	else if (check_shell_command(content, MS_UNSET, ms_unset))
		return ;
	else if (check_shell_command(content, MS_ENV, ms_env))
		return ;
	else if (check_shell_command(content, MS_EXIT, ms_exit))//FIXME работает через раз((
		return ;
	else
	{
		//printf("%s", "HERO");
		ms_exec(content);
	}
	//search(content);
	return ;
}

int		search(char *param)
{
	if (search_pipe(param))
		ms_pipe(param);
	//else if (search_redir(param))
	//	msh_exec_redir(param);
	//printf("%s", "start");
	else if (!(check_shell_command))
		ft_putstr_fd("error", 1);
	return (1);
}

//Написать фуункцию что если мы встретили команду то врубаем шелл брэнч, если пайп то пайп, чек синтакс

void	minishell(char *line)
{
	t_dl_list	*param;

	ft_strdel(&g_ret);
	param = parsing(line);
	while (param)
	{
		printf("|%s|\n", (char *)param->content);
		shell_brach_command((char *)param->content);
		//search((char *)param->content);
		param = (t_dl_list *)param->next;
	}
	param = ft_dl_lstclear(param, free);
}

void		init_env(char **env)
{
	t_env	*data;

	if (!env)
		return ;
	while (*env)
	{
		data = create_env(*env);
		ft_dl_lstadd_back(&g_envlst, ft_dl_lstnew(data));
		data = 0;
		env++;
	}
}

static void		catch_input(char **line)
{
	if (!ft_read_fd(0, line))
	{
		write(2, "\nexit\n", 7);
		exit(g_exit);
	}
}

int				deal_with_input(char **line)
{
	char	*tmp;

	catch_input(line);
	if (**line == '\n')
	{
		free(*line);
		return (0);
	}
	if (*line)
	{
		tmp = ft_strtrim(*line, " ");
		if (*line)
		{
			free(*line);
			*line = NULL;
		}
		*line = tmp;
	}
	return (1);
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
		//if (!deal_with_input(&line)) // FIX
		//	continue;
		line = NULL;
		if (0 > (ft_read_fd(0, &line)))
			ft_putendl_fd(ERROR_READ, 2);
		else
		{
			if (ft_strlen(line))
				line[ft_strlen(line) - 1] = 0;
			ms_dollar(&line);
			minishell(line);
		}
		ft_strdel(&line);
	}
	return (0);
}
