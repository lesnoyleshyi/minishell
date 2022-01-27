/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 18:44:03 by stycho            #+#    #+#             */
/*   Updated: 2021/10/16 18:44:06 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur_node;

	if (!*lst)
		return ;
	cur_node = *lst;
	while (*lst != NULL)
	{
		(*del)(cur_node->content);
		*lst = (*lst)->next;
		free(cur_node);
		cur_node = *lst;
	}
}
