/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 01:17:24 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/07 18:37:37 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *to, const char *from, size_t n)
{
	size_t	size;
	size_t	i;

	if (!to)
		return (0);
	size = ft_strlen(from);
	if (!n)
		return (size);
	i = 0;
	while ((i < n - 1) && from[i])
	{
		to[i] = from[i];
		i++;
	}
	to[i] = '\0';
	return (size);
}

char	**ft_strcp(char **param, int len, int start)
{
	char	**str;
	int		i;

	str = ft_calloc(len + 2, sizeof(char *));
	str[len + 1] = NULL;
	i = 0;
	while (i < (len + 1))
	{
		str[i] = ft_strdup(param[start]);
		start++;
		i++;
	}
	return (str);
}
