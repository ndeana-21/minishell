/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:47:58 by gselyse           #+#    #+#             */
/*   Updated: 2020/11/25 20:21:05 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		search_pipe(char **argv)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (argv[i])
	{
		if (ft_strpass(argv[i], "|" ))
			count++;
		i++;
	}
	return (count);
}

void		pipe_parent(int fd[2], pid_t pid, int status)
{
		if (pid != 0)
		{
			dup2(fd[0], 0);
			close(fd[1]);
			wait(&status); //жду дочку , статус это флаг записи/чтения из какого то дискриптора 
			close(fd[0]);
			exit(EXIT_SUCCESS);
		}
}

void		pipe_child(int child[2], int fd[2], char **s)
{
	if (child == 0) // дочерний процесс
		{
			dup2(fd[1], STDIN_FILENO);
			close(fd[0]);
			execve("/bin/ls", 1, 2);
			close(fd[1]);
			exit(EXIT_SUCCESS);
		}
}

void		msh_pipe(char **s)
{
	int		i;
	char 	**s_parent;
	int		fd[2];
	int		child[2];
	int		status[2];

	i = 0;
	while (!ft_strpass(s[i], "|"))
		i++;
	if (pipe(fd) == -1)
		{
			printf("An error occured with openning to pipe\n");
			errno = EMFILE;
			return ;
		}
	child[0] = fork();
	pipe_parent(child[0], fd, s);
	child[1] = fork();
	pipe_child(child[1], fd, s);
	close(fd[0]);
	close(fd[1]);
	waitpid(child[1], &status[1], 0);
	waitpid(child[0], &status[0], 0);
}
//ls | grep на грепе пайпа нету, execve("usr/bin/grep", 1, 2); dup2(temp_0_fd, 0); - нулевой фдшник на место, по этой причине кат читает из нулевого фдшника
// dup2(fd[1], 1) - в родительском или дочернем, если сделать в дочернем и вызвать exec, то все сохраниться(заменили первый фдшник на первый фдшник пайпа)
// Все что ниже пишется в первый фдшник пайпа
// execve("/bin/ls"..., ...); первый фдшник заменем
// Если встретил пайп, то запускаю функцию пайпа, получаю фд, заменяю первый фдшник на первый фдшник пайпа
// Если встретил пайп на этапе парсинга
// ls | grep ; cat
// редирект это один фдшник либо нулевой либо первый

void	ms_exec(char **param)
{
	int		status;
	char	*path;
	pid_t	pid;

	path = find_env("PATH");
	pid = fork();
	if (pid == 0)
	{
		execve(path, param, g_envlst);
		exit(126);
	}
	wait(&status);
	free(path);
	g_exit = status / 256;
}
