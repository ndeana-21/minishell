/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 00:34:09 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/13 17:30:27 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t size, size_t count)
{
	unsigned char	*ptr;

	ptr = NULL;
	if (!(ptr = (unsigned char *)malloc(count * size)))
		return (NULL);
	ft_memset(ptr, 0, count * size);
	return ((void *)ptr);
}

void	*ft_realloc(void *old_alloc, size_t new_size)
{
	unsigned char	*new_alloc;

	if (!(new_alloc = (unsigned char *)ft_calloc(new_size, 1)))
		return (NULL);
	if (old_alloc)
		new_alloc = ft_memcpy(new_alloc, old_alloc, new_size);
	free(old_alloc);
	return ((void *)new_alloc);
}

int		ft_pagedel(char ***page, size_t len)
{
	if (page)
	{
		while (0 < len)
			free((*page)[--len]);
		free(*page);
	}
	return (-1);
}
