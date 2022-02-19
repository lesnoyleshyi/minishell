/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 00:06:21 by drayl             #+#    #+#             */
/*   Updated: 2022/02/20 00:06:23 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * This function initializes a new element of type "t_file"
 */

t_file	*init_new_file(char *name)
{
	t_file	*file;

	if (name == NULL)
		return (NULL);
	file = (t_file *) malloc(sizeof (t_file));
	if (file == NULL)
		return (NULL);
	file->mod = 0;
	file->name = name;
	file->next = NULL;
	return (file);
}

/**
 * This function to the end of the list
 * of elements of type "t_file" new element
 */

void	add_new_file(t_file **begin, t_file *new)
{
	t_file	*element;

	if (*begin == NULL)
	{
		*begin = new;
		return ;
	}
	element = *begin;
	while (element->next != NULL)
		element = element->next;
	element->next = new;
}

/**
 * This function destroys a linked list of elements of type "t_file"
 */

void	destroy_file(t_file **file)
{
	t_file	*next;

	while (*file != NULL)
	{
		next = (*file)->next;
		free((*file)->name);
		free(*file);
		*file = next;
	}
}
