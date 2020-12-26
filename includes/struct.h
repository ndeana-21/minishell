/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
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

typedef struct			s_pprd
{
	int					fd_rd;
	int					fd_in;
	int					fd_out;
	int					fd_pipe[2][2];
	int					pos;
	pid_t				pid;
	int					count;
	int					status;
}						t_pprd;

#endif
