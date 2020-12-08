/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:47:58 by gselyse           #+#    #+#             */
/*   Updated: 2020/12/08 14:50:19 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		pipe_parent(int child, int fd[2], char **param)
{
	if (child == 0)
	{
		dup2(fd[1], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		shell_brach_command(param);
		exit(EXIT_SUCCESS);
	}
}

void		pipe_child(int child[2], int fd[2], char **param)
{
	if (child == 0) // дочерний процесс
		{
			dup2(fd[0], STDIN_FILENO); // Дублируем входную сторону трубы в стандартный ввод
			close(fd[0]); // Закрываем стандартный ввод дочернего элемента
			close(fd[1]);
			shell_brach_command(param);
			exit(EXIT_SUCCESS);
		}
}

void		ms_pipe(t_dl_list *param)
{
	int		i;
	char	**param_parent;
	int		fd[2];
	int		child[2];
	int		status[2];

	i = 0;
	//printf("%s", "Heello");
	//printf("%s", param);
	param_parent = ((char *)ft_dl_lstnnext(param, -1)->content);
	param = ((char *)ft_dl_lstnnext(param, 1)->content);
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("An error occured with openning to pipe\n", 1);
		errno = EMFILE;
		return ;
	}
	child[0] = fork();
	pipe_parent(child[0], fd, param_parent);
	//ft_freestrs(param_parent);
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
// сигнал + exit + pipe + redirect + лики + "

