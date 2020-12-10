/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:09:42 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/10 18:24:01 by ndeana           ###   ########.fr       */
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

t_dl_list	*g_envlst;
char		*g_name;
int			g_exit;

void		error_exit(size_t error_code, char *error_text);
void		print_error(size_t error_code, char *error_text);
t_dl_list	*parsing(char *line);
void		prompt(void);
void		ms_dollar(char **str);

void		shell_brach_command(char *content);
void		minishell(char **line);

void		init_env(char **env);
void		free_env(void *env);
t_env		*create_env(char *str);
t_dl_list	*find_env(char *name);
void		replace_env(char *name, char *str);

void		ms_cd(char *param);
void		ms_pwd(char *param);
void		ms_env(char *param);
void		ms_echo(char *param);
void		ms_exit(char *param);
void		ms_exec(char *param);
void		ms_unset(char *param);
void		ms_export(char *param);
void		ms_sep(t_dl_list *param);
void		ms_pipe(t_dl_list *param);
void		ms_redir(t_dl_list *param, int perm, int descr, int to_dup);

void		set_signal(void);
void		signal_handler(int signum);
char		*find_path(char *param);
int			ft_puterr(char *str1, char *str2, char *str3, int error);
void		ft_freestrs(char **str);

#endif
