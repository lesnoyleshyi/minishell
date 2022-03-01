/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 00:06:30 by drayl             #+#    #+#             */
/*   Updated: 2022/02/20 00:06:31 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This function removes an element of type "t_list"
 * from the linked list and returns a pointer to the
 * element that replaced the removed one. If the
 * removed element is the last one, "NULL" is returned.
 */

t_list	*remove_element(t_list **begin, t_list *element)
{
	t_list	*item;
	t_list	*right;

	if (element == *begin)
		*begin = element->next;
	else
	{
		item = *begin;
		while (item != NULL && item->next != element)
			item = item->next;
		if (item != NULL)
			item->next = element->next;
	}
	right = element->next;
	if (element->content != NULL)
		free(element->content);
	free(element);
	return (right);
}

/**
 * This function removes the first element of the list
 */

void	remove_first_element(t_list **begin)
{
	t_list	*element;

	if (begin == NULL || *begin == NULL)
		return ;
	element = (*begin)->next;
	if ((*begin)->content != NULL)
		free((*begin)->content);
	free(*begin);
	*begin = element;
}

/**
 * This function clears the entire passed list
 */

void	remove_all_list(t_list **begin)
{
	while (*begin != NULL)
		remove_first_element(begin);
}
