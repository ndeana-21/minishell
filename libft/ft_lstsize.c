/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 01:22:26 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/07 21:57:02 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

size_t	ft_dl_lstsize(t_dl_list *lst)
{
	size_t	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst)
	{
		lst = (t_dl_list*)lst->next;
		i++;
	}
	return (i);
}

size_t	ft_dl_lstpos(t_dl_list *lst)
{
	size_t	pos;

	pos = 0;
	if (lst)
		while (lst->prev)
		{
			lst = (t_dl_list *)lst->prev;
			pos++;
		}
	return (pos);
}
