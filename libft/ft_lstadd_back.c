/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 16:26:03 by stycho            #+#    #+#             */
/*   Updated: 2021/10/16 16:26:05 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*elem;

	if (lst == NULL || *lst == NULL)
		*lst = new;
	else
	{
		elem = *lst;
		while (elem->next != NULL)
			elem = elem->next;
		elem->next = new;
	}
}
