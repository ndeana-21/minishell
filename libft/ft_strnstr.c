/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 01:17:55 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/10 17:25:44 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *find, size_t n)
{
	size_t	i_find;
	size_t	i_s;

	if (!*find)
		return ((char*)s);
	i_s = 0;
	while (s[i_s] && i_s < n)
	{
		i_find = 0;
		while (find[i_find] && (find[i_find] == s[i_s + i_find]) &&
				((i_s + i_find) < n))
			i_find++;
		if (!find[i_find])
			return ((char*)&s[i_s]);
		i_s++;
	}
	return (0);
}

char	*ft_strncut(char *s, size_t n)
{
	char	*ret;
	size_t	i;

	if (!s)
		return (0);
	if (!(ret = (char *)ft_calloc(n + 1, sizeof(char))))
		return (0);
	i = -1;
	while (s[++i] && (n >= i))
		ret[i] = s[i];
	return (ret);
}

char					*ft_strinsert(char *str, char *target, size_t to)
{
	size_t	str_count;
	size_t	count;
	char	*ret;

	if (!(ret = ft_calloc(sizeof(char), ft_strlen(target) + ft_strlen(str))))
		return (NULL);
	count = 0;
	while (str[count] && (count < to))
	{
		ret[count] = str[count];
		count++;
	}
	str_count = count;
	while (*target)
	{
		ret[count++] = *target;
		target++;
	}
	while (str[str_count])
		ret[count++] = str[str_count++];
	free (str);
	return (ret);
}
