/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 06:57:05 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/23 20:47:16 by ndeana           ###   ########.fr       */
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

typedef struct			s_pipe
{
	int					fd[2][2];
	int					pos;
	pid_t				pid;
	int					count;
	int					status;
}						t_pipe;

#endif
