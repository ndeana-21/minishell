/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 03:37:33 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/15 14:43:39 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(size_t error_code, char *error_text)
{
	if (error_text)
		ft_putendl_fd(error_text, 2);
	g_exit = error_code;
}

void	error_exit(size_t error_code, char *error_text)
{
	print_error(error_code, error_text);
	exit(error_code);
}

int		ft_puterr(char *str1, char *str2, char *str3, int error)
{
	ft_putstr_fd("sh :", 1);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putendl_fd(str3, 2);
	g_exit = 1;
	return (error);
}
