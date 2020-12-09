/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:13:19 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/09 22:28:50 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO exit "
//TODO cd ~/ SEGA

int		check_shell_command(char *content, char *command, void (*func)(char *))
{
	char	*buff;

	if (ft_strlen(command) == (size_t)ft_strcmp_reg(content, command))
	{
		if (content[ft_strlen(command)] == '\0' ||
			content[ft_strlen(command)] == ' ')
		{
			buff = ft_strreplace(content, "", 0, ft_strlen(command));
			buff = ft_strpass_rev(buff, " ");
			func(ft_strpass(buff, " "));
			free(buff);
		}
		return (TRUE);
	}
	return (FALSE);
}

void	shell_brach_command(char *content)
{
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
	else if (check_shell_command(content, MS_EXIT, ms_exit))
		return ;
	else
		ms_exec(content);
}

void	ms_run(t_dl_list *param)
{
	if (!(ft_dl_lstnnext(param, -1)->prev))
		shell_brach_command((char *)(ft_dl_lstnnext(param, -1)->content));
	if (!(ft_dl_lstnnext(param, 1)->next))
		shell_brach_command((char *)(ft_dl_lstnnext(param, 1)->content));
	else if (ft_strsame(ft_dl_lstnnext(param, 2)->content, ";"))
		shell_brach_command((char *)(ft_dl_lstnnext(param, 1)->content));
}

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

void	shell_branch_sep(t_dl_list *param)
{
	if (ft_strsame(param->content, ";"))
		ms_run(param);
	else if (ft_strsame(param->content, "|"))
		ms_pipe(param);
	else if (ft_strsame(param->content, "<"))
		ms_redir(param, O_RDONLY, 0644, 0);
	else if (ft_strsame(param->content, ">"))
		ms_redir(param, O_WRONLY | O_CREAT | O_TRUNC, 0744, 1);
	else if (ft_strsame(param->content, ">>"))
		ms_redir(param, O_WRONLY | O_CREAT | O_APPEND, 0744, 1);
}

void	minishell(char *line)
{
	t_dl_list	*param;

	ft_strdel(&g_ret);
	param = parsing(line);
	if (!(param->next))
		shell_brach_command((char *)param->content);
	while (param)
	{
		shell_branch_sep(param);
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
	(void)argv;
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

//FIXME комманды с параметрами работают и без пробела между коммандой и параметром