/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 00:06:13 by drayl             #+#    #+#             */
/*   Updated: 2022/02/20 00:06:14 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This function creates an element
 * of type "t_data" with null values
 */

t_data	*create_data(void)
{
	t_data	*data;

	data = (t_data *) malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->file = NULL;
	data->command = NULL;
	data->next = NULL;
	data->param_list = NULL;
	return (data);
}

/**
 * This function destroys an object
 * of type "t_data" passed as a parameter
 */

void	destroy_data(t_data	**data)
{
	t_data	*el;

	while (*data != NULL)
	{
		el = (*data)->next;
		destroy_file(&((*data)->file));
		destroy_array((*data)->command);
		destroy_param(&(*data)->param_list);
		free(*data);
		*data = el;
	}
}

/**
 * This function creates a new element of type "t_data"
 * and adds it to the "next" field in the "data" variable,
 * after which the pointer to the structure changes
 * its value to a pointer to the new element
 */

int	add_new_data(t_data **data)
{
	t_data	*new;

	new = create_data();
	if (new == NULL)
		return (MEMORY_ERROR);
	(*data)->next = new;
	*data = new;
	return (OK);
}

/**
 * This function acts as a general parser and returns
 * a list of elements of type "t_data". In case of
 * unsuccessful processing, it will return "NULL"
 */

t_data	*init_data(const char *line)
{
	t_data	*data;
	t_list	*begin;

	begin = NULL;
	data = create_data();
	if (data == NULL)
		memory_error();
	first_pars(line, &begin);
	if (begin == NULL)
		memory_error();
	if (second_parser(&begin, data) == SYNTAX_ERROR)
	{
		destroy_data(&data);
		return (NULL);
	}
	read_heredoc(data);
	return (data);
}
