/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 00:06:53 by drayl             #+#    #+#             */
/*   Updated: 2022/02/20 00:06:54 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This function removes an array of strings
 */

char	**destroy_array(char **mas)
{
	int	i;

	if (mas == NULL)
		return (NULL);
	i = -1;
	while (mas[++i] != NULL)
		free(mas[i]);
	free(mas);
	return (NULL);
}

/**
 * This function calculates the position of "element" in the linked list
 */

static int	get_index_element(t_list *begin, t_list *element)
{
	int	index;

	index = 0;
	while (begin != NULL)
	{
		if (begin == element)
			return (index);
		++index;
		begin = begin->next;
	}
	return (index);
}

/**
 * This function converts the part (up to the "stop" element)
 * of the linked list into an array of strings
 */

char	**convert_sublist_to_array(t_list *begin, t_list *stop)
{
	int		size;
	int		index;
	char	**mas;

	if (begin == NULL)
		return (NULL);
	size = get_index_element(begin, stop) + 1;
	mas = (char **) malloc(sizeof (char *) * (size));
	if (mas == NULL)
		return (NULL);
	index = 0;
	while (index < size - 1)
	{
		if (begin->content != NULL)
			mas[index++] = begin->content;
		remove_all_quote(begin->content);
		begin->content = NULL;
		begin = begin->next;
	}
	mas[index] = NULL;
	return (mas);
}

/**
 * This function converts the entire list to a list of strings
 */

char	**convert_list_to_array(t_list *lst)
{
	int		size;
	int		index;
	char	**mas;

	if (lst == NULL)
		return (NULL);
	size = ft_lstsize(lst) + 1;
	mas = (char **) malloc((size) * sizeof (char *));
	if (mas == NULL)
		return (NULL);
	index = 0;
	while (index < size - 1)
	{
		lst->content = replace_all_param(lst->content);
		remove_all_quote(lst->content);
		if (lst->content != NULL)
			mas[index++] = lst->content;
		lst->content = NULL;
		lst = lst->next;
		if (lst == NULL)
			break ;
	}
	mas[index] = NULL;
	return (mas);
}
