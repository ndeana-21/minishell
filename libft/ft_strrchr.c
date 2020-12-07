/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 01:17:49 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/07 19:00:00 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*r;

	r = 0;
	while (*s)
	{
		if (*s == c)
			r = (char *)s;
		s++;
	}
	if (r)
		return (r);
	if (c == '\0')
		return ((char*)s);
	return (0);
}

char			*ft_strpass(char *str, char *sample)
{
	while (*str)
	{
		if (ft_strchr(sample, *str))
			str++;
		else
			return (str);
	}
	return (str);
}

char					*ft_strpass_rev(char *str, char *sample)
{
	size_t	count;

	count = ft_strlen(str);
	while (--count > 0)
	{
		if (ft_strchr(sample, str[count]))
			str[count] = 0;
		else
			break ;
	}
	return (str);
}
