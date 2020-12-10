/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 01:22:42 by ndeana            #+#    #+#             */
/*   Updated: 2020/12/10 00:42:43 by ndeana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tlst;

	if (!lst)
		return (0);
	if (!(*lst))
	{
		*lst = new;
		if (!new)
			return (0);
		return (1);
	}
	tlst = ft_lstlast(*lst);
	tlst->next = new;
	if (!new)
		return (0);
	return (1);
}

int		ft_dl_lstadd_back(t_dl_list **lst, t_dl_list *new)
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
	tlst = ft_dl_lstlast(*lst);
	tlst->next = (struct t_dl_list*)new;
	new->prev = (struct t_dl_list*)tlst;
	if (!new)
		return (0);
	return (1);
}

void	ft_dl_lstinsert(t_dl_list *lst, t_dl_list *new, size_t to)
{
	t_dl_list	*tmp;

	lst = ft_dl_lstnnext(ft_dl_lstfirst(lst), to);
	tmp = (t_dl_list *)lst->next;
	lst->next = (struct t_dl_list *)new;
	new->prev = (struct t_dl_list *)lst;
	new->next = (struct t_dl_list *)tmp;
}

void	ft_dl_lstreplace(t_dl_list *lst, size_t to)
{
	t_dl_list	*tmp;

	if (!lst)
		return ;
	if (lst->prev)
		((t_dl_list *)lst->prev)->next = lst->next;
	if (lst->next)
		((t_dl_list *)lst->next)->prev = lst->prev;
	tmp = ft_dl_lstnnext(ft_dl_lstfirst(lst), to);
	if (tmp->prev)
		((t_dl_list *)tmp->prev)->next = (struct t_dl_list *)lst;
	lst->prev = tmp->prev;
	lst->next = (struct t_dl_list *)tmp;
	tmp->prev = (struct t_dl_list *)lst;
}
