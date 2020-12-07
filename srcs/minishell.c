/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:13:19 by ndeana            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/12/07 21:18:02 by gselyse          ###   ########.fr       */
=======
/*   Updated: 2020/12/07 20:51:54 by ndeana           ###   ########.fr       */
>>>>>>> add20648ee41071e1e7a3ee3e8fc45ad7e57f442
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
	else if (ft_strsame(content, "|"))
	{
		printf("%s", "HERO\n");
		ms_pipe(content);
		return ;
	}
	else
	{
		//printf("%s", "HERO");
		ms_exec(content);
	}
	//search(content);
	return ;
}
/*
int		search(char *param)
{
	if (search_pipe(param))
		ms_pipe(param);
	//else if (search_redir(param))
	//	msh_exec_redir(param);
	//printf("%s", "start");
	//else if (!(shell_brach_command(param)))
		ft_putstr_fd("error", 1);
	return (1);
}
*/
//Написать фуункцию что если мы встретили команду то врубаем шелл брэнч, если пайп то пайп, чек синтакс

void	minishell(char *line)
{
	t_dl_list	*param;

	ft_strdel(&g_ret);
	param = parsing(line);
	while (param)
	{
		// printf("|%s|\n", (char *)param->content);
		shell_brach_command((char *)param->content);
		//search((char *)param->content);
		param = (t_dl_list *)param->next;
	}
	param = ft_dl_lstclear(param, free);
}

void		init_env(char **env)
{
	t_env	*data;

	g_envlst = NULL;
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

void				deal_with_input(char **line)
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

int			main(int argc, char **argv, char **env)
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
			minishell(line);
			ft_strdel(&line);
		}
	}
	return (0);
}
