/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:09:42 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/19 22:03:54 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "error.h"
# include "struct.h"
# include "libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>

# define TRUE		1
# define FALSE		0
# define MS_ECHO	"echo"
# define MS_CD		"cd"
# define MS_PWD		"pwd"
# define MS_EXPORT	"export"
# define MS_UNSET	"unset"
# define MS_ENV		"env"
# define MS_EXIT	"exit"
# define REDIR_OUT		1
# define REDIR_APPEND	2
# define REDIR_IN		3


t_dl_list	*g_envlst;
char		*g_name;
char		*g_path;
int			g_exit;
int			g_child;
int			g_fd[2][2];

void		error_exit(size_t error_code, char *error_text);
void		print_error(size_t error_code, char *error_text);
t_dl_list	*parsing(char *line);
void		prompt(void);
void		ms_dollar(char **str);
char		find_quotes(char line, char flag);

void        shell_brach_cmd(char *content);
void        shell_branch_sep(t_dl_list *param, int *fd_count);
void		minishell(char **line);

char		**create_env_exec(void);
void		free_env(void *env);
t_env		*create_env(char *str);
t_dl_list	*find_env(char *name);
void		replace_env(char *name, char *str);

void		ms_cd(char **param);
void		ms_pwd(char **param);
void		ms_env(char **param);
void		ms_echo(char **param);
void		ms_exit(char **param);
void		ms_exec(char **param);
void		ms_unset(char **param);
void		ms_export(char **param);
void		ms_sep(t_dl_list *param);
<<<<<<< Updated upstream
void		ms_pipe(t_dl_list *param);
void		ms_redir(t_dl_list *param, int perm, int descr, int to_dup, int *fd_count);
=======
void		ms_pipe(t_dl_list *param, int *fd_count);
void		ms_redir(t_dl_list *param, int perm, int descr, int to_dup);

>>>>>>> Stashed changes
void		set_signal(void);
void		signal_handler(int signum);
char		*find_path(char *param);
int			ft_puterr(char *str1, char *str2, char *str3, int error);
void		ft_freestrs(char **str);

#endif
