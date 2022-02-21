/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 23:19:28 by drayl             #+#    #+#             */
/*   Updated: 2021/10/13 23:19:31 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*begin;
	t_list	*el;

	if (!lst || !f)
		return ((t_list *)0);
	begin = ft_lstnew(f(lst->content));
	if (!begin)
		return (begin);
	lst = lst->next;
	while (lst)
	{
		el = ft_lstnew(f(lst->content));
		if (!el)
		{
			del(begin->content);
			ft_lstclear(&begin, del);
			return ((t_list *)0);
		}
		ft_lstadd_back(&begin, el);
		lst = lst->next;
	}
	return (begin);
}
