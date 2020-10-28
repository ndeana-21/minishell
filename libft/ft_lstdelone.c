/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 01:22:50 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/13 18:06:30 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst)
		return (lst);
	if (del)
		del(lst->content);
	free(lst);
	return (NULL);
}
