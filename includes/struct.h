/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 06:57:05 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/19 00:40:44 by gselyse          ###   ########.fr       */
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

typedef struct	s_redir
{
	int		state;
	char	pad[4];
	char	*file;
	char	*original;
}				t_redir;

typedef struct	s_pipe
{
	char		*line;
	char		**argv;
}				t_pipe;

#endif
