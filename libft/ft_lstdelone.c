/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 01:22:50 by ndeana            #+#    #+#             */
/*   Updated: 2020/11/11 21:00:53 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (del && lst)
		del(lst->content);
	else
		return (lst);
	free(lst);
	return (NULL);
}

t_dl_list	*ft_dl_lstdelone(t_dl_list *lst, void (*del)(void*))
{
	if (del && lst)
		del(lst->content);
	else
		return (lst);
	if (lst->prev)
		((t_dl_list *)lst->prev)->next = lst->next;
	if (lst->next)
		((t_dl_list *)lst->next)->prev = lst->prev;
	free(lst);
	return (NULL);
}
