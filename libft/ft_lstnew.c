/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 01:22:04 by ndeana            #+#    #+#             */
/*   Updated: 2020/10/13 17:52:34 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = NULL;
	if (!(list = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

char	**ft_lsttopage(t_list *lst, int *y)
{
	int		i;
	char	**dmas;

	if (!lst)
		return (NULL);
	*y = ft_lstsize(lst);
	if (!(dmas = (char **)ft_calloc(ft_lstsize(lst), sizeof(char *))))
		return (NULL);
	i = 0;
	while (i < *y)
	{
		if (!(dmas[i++] = ft_strdup(lst->content)))
			return (NULL);
		lst = lst->next;
	}
	return (dmas);
}
