/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:09:42 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/30 21:13:42 by gselyse          ###   ########.fr       */
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
# define MS_ECHO	"echo "
# define MS_CD		"cd "
# define MS_PWD		"pwd"
# define MS_EXPORT	"export "
# define MS_UNSET	"unset "
# define MS_ENV		"env"
# define MS_EXIT	"exit"

char		*g_name;
char		*g_ret;
t_dl_list	*g_envlst;
int			g_exit;

void		error_exit(size_t error_code, char *error_text);
t_dl_list	*parsing(char *line);
t_dl_list	*find_env(char *name);
t_env		*create_env(char *str);
t_env		*free_env(t_env *env);

void		ms_echo(char *param);
void		ms_cd(char *param);
void		ms_pwd(char **param);
void		ms_export(char *param);
void		ms_unset(char *param);
void		ms_env(char *param);
void		ms_exit(char **param);
void		set_signal(void);
void		signal_handler(int signum);
void		promt(void);
void        ms_exec(char *param);


void		ms_dollar(char **str);
char		*make_dollar(char *str, size_t *insted);


#endif
