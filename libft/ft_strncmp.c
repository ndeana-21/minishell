/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 01:16:29 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/17 05:17:18 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!n || (!s1 && !s2))
		return (0);
	i = 0;
	while (s1[i] && s2[i] && (i < (n - 1)) &&
			((unsigned char)s1[i] == (unsigned char)s2[i]))
		i++;
	return (s1[i]);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 && !s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && ((unsigned char)s1[i] == (unsigned char)s2[i]))
		i++;
	return (i);
}

int	ft_strsame(const char *str1, const char *str2)
{
	size_t	count;

	count = 0;
	if (!str1 || !str2)
		return (0);
	if (ft_strlen(str1) == ft_strlen(str2))
	{
		while (str1[count] && str2[count])
		{
			if (str1[count] != str2[count])
				return (0);
			count++;
		}
		if (!str1[count] && !str2[count])
			return (1);
	}
	return (0);
}
