/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 01:17:49 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/12 16:34:12 by ndeana           ###   ########.fr       */
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

char	*ft_strpass(char *str, char *sample)
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

char	*ft_strpass_rev(char *str, char *sample)
{
	size_t	count;

	count = ft_strlen(str);
	while (--count)
	{
		if (ft_strchr(sample, str[count]))
			str[count] = 0;
		else
			break ;
	}
	return (str);
}

void	ft_erasechr(char *str, const char *sample)
{
	size_t	i;

	if (!str)
		return ;
	while (*str)
	{
		if (ft_strchr(sample, *str))
		{
			i = 0;
			while (str[i++])
				str[i - 1] = str[i];
		}
		else
			str++;
	}
}

void	ft_strmoveleft(char *str)
{
	size_t	i;

	i = 0;
	while (str[++i])
		str[i - 1] = str[i];
	str[i - 1] = 0;
}
