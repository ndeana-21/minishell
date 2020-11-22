/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 00:35:06 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/22 07:24:23 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dub;
	size_t	i;

	dub = NULL;
	if (!(dub = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	i = -1;
	while (s[++i])
		dub[i] = s[i];
	dub[i] = '\0';
	return (dub);
}

void	ft_strappend(char *str, char *from, size_t size)
{
	size_t	count;

	if (!str || !from)
		return ;
	count = ft_strlen(str) - 1;
	while (*from && (++count < size))
	{
		str[count] = *from;
		from++;
	}
}
