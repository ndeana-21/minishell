/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 06:57:05 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/22 00:32:22 by gselyse          ###   ########.fr       */
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
	int					exist;
}						t_pipe;

#endif
