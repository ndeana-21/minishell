/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:25:18 by gselyse           #+#    #+#             */
/*   Updated: 2020/11/15 15:39:27 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		search_redir(char **argv)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (argv[i])
	{
		if ((ft_strpass(argv[i], ">") || (ft_strpass(argv[i], ">>") || (ft_strpass(argv[i], "<")))))
			count++;
		i++;
	}
	return (count);
}

int		type_redir(char *argv)
{

	if (ft_strpass(argv, ">"))
		return ();
	else if (ft_strpass(argv, ">>"))
		return ();
	else
		return ();
}