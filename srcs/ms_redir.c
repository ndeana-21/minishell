/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:25:18 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/15 22:02:26 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_redir(t_dl_list *param, int perm, int descr, int to_dup)
{
	int		fd;
	char	*tmp;
	char	*tmp_p;
	char	*bmm;
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
		sort(bmm);
		exit(EXIT_SUCCESS);
	}
	//free(tmp);
	//free(tmp_p);
	wait(&g_exit);
	g_exit = g_exit / 256;
}

void		init_redir(char *command, t_redir *r)
{
	int num;

	num = 0;
	while (*command)
	{
		if (ft_strchr("><", *command))
			num++;
		command++;
	}
	r->argc = num + 1;
	r->argv = (char **)malloc(sizeof(char *) * (r->argc + 1));
	r->types = (char *)malloc(sizeof(char) * (r->argc + 1));
	r->cmds = NULL;
}

int			parse_redir_final(t_redir *r, int j)
{
	if (has_redir_syntax_error(r->argv[j]))
		return (-1);
	r->types[j++] = 0;
	r->argv[j] = 0;
	r->argc = j;
	return (1);
}

int			parse_redir(char *command, t_redir *r)
{
	int		i;
	int		j;
	int		start;

	i = -1;
	j = 0;
	start = 0;
	while (command[++i])
	{
		if (ft_strchr("><", command[i]))
		{
			if (j > 0 && ((r->types[0] == BREDIR && command[i] != '<') ||
				(r->types[0] != BREDIR && command[i] == '<')))
				return (0);
			r->argv[j] = substr_and_trim(command, start, i - start, " ");
			if (j == 0)
				r->cmds = ft_split(r->argv[j], ' ');
			r->types[j] = find_redir_type(command, i);
			r->types[j++] == DREDIR ? i++ : 0;
			start = i + 1;
		}
	}
	r->argv[j] = substr_and_trim(command, start, i - start, " ");
	return (parse_redir_final(r, j));
}

void		open_unnecessary_files(t_redir *r)
{
	int	i;
	int	fd;

	i = 1;
	while (i < r->argc - 1)
	{
		if (i > 1)
			close(fd);
		if (r->types[i - 1] == REDIR)
			fd = open(r->argv[i], O_WRONLY | O_CREAT | O_TRUNC, 0744);
		else if (r->types[i - 1] == DREDIR)
			fd = open(r->argv[i], O_WRONLY | O_CREAT | O_APPEND, 0744);
		else
			fd = open(r->argv[i], O_RDONLY, 0644);
		i++;
	}
	close(fd);
}

void		exec_redir(char *line, t_list *envs)
{
	int		i;
	int		ret;
	t_redir r;

	init_redir(line, &r);
	if ((ret = parse_redir(line, &r)) <= 0)
	{
		if (ret < 0)
			ft_putendl_fd("syntax error near unexpected token `newline'", 1);
		return ;
	}
	i = -1;
	while (r.cmds[++i])
	{
		if (has_quote(r.cmds[i]))
			r.cmds[i] = modify_argv(r.cmds[i], envs);
	}
	open_unnecessary_files(&r);
	cmd_redir(&r, envs);
}

static int		do_redir(t_redir *r, t_list *envs)
{
	int		fd;
	char	*path;

	fd = open(r->argv[r->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (fd < 0)
	{
		ft_puterror_fd(r->argv[r->argc - 1], ": No such file or directory", 2);
		return (EXIT_FAILURE);
	}
	if (!(path = find_path(r->cmds[0], envs)))
		return (ft_puterror_fd(r->cmds[0], ": command not found", 2));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (!exec_builtin(r->argv[r->argc - 1], envs) &&
		(execve(path, r->cmds, g_envp) == -1))
		return (ft_puterror_fd(r->cmds[0], ": command not found", 2));
	free(path);
	free_double_arr(r->cmds);
	return (EXIT_SUCCESS);
}

static int		do_dredir(t_redir *r, t_list *envs)
{
	int		fd;
	char	*path;

	fd = open(r->argv[r->argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0744);
	if (fd < 0)
	{
		ft_puterror_fd(r->argv[r->argc - 1], ": No such file or directory", 2);
		return (EXIT_FAILURE);
	}
	if (!(path = find_path(r->cmds[0], envs)))
		return (ft_puterror_fd(r->cmds[0], ": command not found", 2));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (!exec_builtin(r->argv[r->argc - 1], envs) &&
		(execve(path, r->cmds, g_envp) == -1))
		return (ft_puterror_fd(r->cmds[0], ": command not found", 2));
	free(path);
	free_double_arr(r->cmds);
	return (EXIT_SUCCESS);
}

static int		do_bredir(t_redir *r, t_list *envs)
{
	int		fd;
	char	*path;

	fd = open(r->argv[r->argc - 1], O_RDONLY, 0644);
	if (fd < 0)
	{
		ft_puterror_fd(r->argv[r->argc - 1], ": No such file or directory", 2);
		return (EXIT_FAILURE);
	}
	if (!(path = find_path(r->cmds[0], envs)))
		return (ft_puterror_fd(r->cmds[0], ": command not found", 2));
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (!exec_builtin(r->argv[r->argc - 1], envs) &&
		(execve(path, r->cmds, g_envp) == -1))
		return (ft_puterror_fd(r->cmds[0], ": command not found", 2));
	free(path);
	free_double_arr(r->cmds);
	return (EXIT_SUCCESS);
}

void			cmd_redir(t_redir *r, t_list *envs)
{
	int		i;
	int		ret;
	int		status;
	pid_t	child;

	i = 0;
	child = fork();
	if (child == 0)
	{
		if (r->types[r->argc - 2] == REDIR)
			ret = do_redir(r, envs);
		else if (r->types[r->argc - 2] == DREDIR)
			ret = do_dredir(r, envs);
		else
			ret = do_bredir(r, envs);
		exit(ret);
	}
	wait(&status);
	g_exit_value = status / 256;
	free(r->types);
	free_double_arr(r->argv);
	free_double_arr(r->cmds);
}
