/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 01:22:14 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/07 23:35:50 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst)
		return (0);
	if (!(*lst))
	{
		*lst = new;
		if (!new)
			return (0);
		return (1);
	}
	new->next = *lst;
	*lst = new;
	return (1);
}

int	ft_dl_lstadd_front(t_dl_list **lst, t_dl_list *new)
{
	t_dl_list	*tlst;

	if (!lst)
		return (0);
	if (!(*lst))
	{
		*lst = new;
		if (!new)
			return (0);
		return (1);
	}
	tlst = ft_dl_lstfirst(*lst);
	new->next = (struct t_dl_list*)tlst;
	*lst = new;
	return (1);
}
