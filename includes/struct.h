/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 06:57:05 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/26 17:09:35 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "libft.h"

typedef struct			s_env
{
	char				*name;
	char				*val;
}						t_env;

typedef struct			s_redir
{
	int					fd;
	int					fd_in;
	int					fd_out;
	int					type;
	int					count;
	int					*status;
}						t_redir;
typedef struct			s_pipe
{
	int					fd[2][2];
	int					pos;
	pid_t				pid;
	int					count;
	int					status;
}						t_pipe;

#endif
