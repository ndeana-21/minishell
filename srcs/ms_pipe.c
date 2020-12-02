/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:47:58 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/02 21:11:06 by gselyse          ###   ########.fr       */
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

void	sort(char **param)
{
	if (search_pipe(param))
		ms_pipe(param);
	//else if (search_redir(param))
	//	msh_exec_redir(param);
	else if (!shell_brach_command(param))
		ms_exec(param);
}

void		pipe_parent(int child, int fd[2], char **param)
{
		if (child != 0)
		{
			dup2(fd[1], STDIN_FILENO); 
			close(fd[0]);
			//wait(&status); //жду дочку , статус это флаг записи/чтения из какого то дискриптора 
			close(fd[1]);
			sort(param);
			exit(EXIT_SUCCESS);
		}
}

void		pipe_child(int child[2], int fd[2], char **param)
{
	if (child == 0) // дочерний процесс
		{
			dup2(fd[0], STDIN_FILENO); // Дублируем входную сторону трубы в стандартный ввод
			close(fd[0]); // Закрываем стандартный ввод дочернего элемента
			//execve("/bin/ls", 1, 2);
			close(fd[1]);
			sort(param);
			exit(EXIT_SUCCESS);
		}
}

void		ms_pipe(char **param)
{
	int		i;
	char 	**param_parent;
	int		fd[2];
	int		child[2];
	int		status[2];

	i = 0;
	while (!ft_strpass(param[i], "|"))
		i++;
	if (pipe(fd) == -1)
		{
			printf("An error occured with openning to pipe\n");
			errno = EMFILE;
			return ;
		}
	child[0] = fork();
	pipe_parent(child[0], fd, param);
	//чистка строки
	child[1] = fork();
	pipe_child(child[1], fd, param);
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
	char	**elem;
	pid_t	pid;

	elem = ft_split(param, ' ');
	printf("%s", "\nHERO");
	//path = find_path(param[0]);
	if (!(path = find_path(param[0])))
	{
		ft_puterr(param[0], ": command not found", "", 127);
		return ;
	}
	path = ft_strjoin(path, elem[0]);
	pid = fork();
	if (pid == 0)
	{
		if (opendir(path) != NULL)
			exit(ft_puterr(param[0], ": is a directory", "", 126));
		if (execve(path, &(param[1]), g_envlst) == -1)
		{
			if (errno == 13 || errno == 8)
				exit(ft_puterr(param[0], ": Permission denied", "", 126));
			exit(ft_puterr(param[0], ": command not found", "", 127));
		}
		exit(EXIT_SUCCESS);
	}
	wait(&status);
	free(path);
	g_exit = status / 256;
}

char			find_path(char *param)
{
	int			i;
	char		*tmp;
	char		*path;
	char		**paths;
	struct stat	s;

	if (!(tmp = find_env("PATH")))
		return (NULL);
	paths = ft_split(tmp, ':');
	free(tmp);
	i = -1;
	while (paths[++i])
	{
		//tmp = ft_strjoin("/", param); // тут сега
		path = ft_strjoin(paths[i], tmp);
		//free(tmp);
		if (stat(path, &s) == 0)
		{
			ft_freestrs(paths);
			return (path);
		}
		free(path);
	}
	ft_freestrs(paths);
	return (ft_strdup(param));
}
