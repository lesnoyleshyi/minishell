/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:59:11 by drayl             #+#    #+#             */
/*   Updated: 2022/02/19 23:59:13 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * This function removes elements of type "t_list"
 * containing modifiers and adds a new element of
 * type "t_file" to the structure of type "t_data"
 */

static int	processing_file(t_list **begin, t_list **element,
						t_data *data, int mod)
{
	t_file	*file;
	char	*name;

	*element = remove_element(begin, *element);
	if (*element == NULL)
		return (SYNTAX_ERROR);
	mod = get_mod_file(begin, element, mod);
	if (*element == NULL)
		return (SYNTAX_ERROR);
	if (check_content((*element)->content, FALSE) != E_NOT_SPEC_SYM)
		return (SYNTAX_ERROR);
	name = ft_strdup((*element)->content);
	if (name == NULL)
		return (MEMORY_ERROR);
	name = replace_all_param(name);
	remove_all_quote(name);
	file = init_new_file(name);
	if (file == NULL)
		return (MEMORY_ERROR);
	file->mod = mod;
	add_new_file(&(data->file), file);
	*element = remove_element(begin, *element);
	return (OK);
}

/**
 * This function converts the received string into a variable
 * of type "t_param" and stores it in the global variable "common"
 */

static int	add_new_param(t_list **begin, t_list **element)
{
	t_param	*param;

	param = init_param((*element)->content);
	*element = remove_element(begin, *element);
	if (param == NULL)
		return (MEMORY_ERROR);
	add_param(&g_common->new_list, param);
	return (OK);
}

/**
 * This function removes the element containing "|" writes
 * all the necessary data to a variable of type "t_data"
 * and initializes a new variable of this type
 */

static int	processing_pipe(t_list **begin, t_list **element, t_data **data)
{
	(*data)->command = convert_sublist_to_array(*begin, *element);
	if ((*data)->command == NULL)
		return (MEMORY_ERROR);
	(*data)->param_list = g_common->new_list;
	g_common->new_list = NULL;
	while (*begin != NULL && *begin != *element)
		remove_first_element(begin);
	if (*element != NULL && *begin == *element)
	{
		remove_first_element(element);
		*begin = *element;
	}
	return (add_new_data(data));
}

/**
 * This function executes the appropriate command for each content type
 */

static int	processing_element(t_list **begin, t_list **element, t_data **data)
{
	int	type;

	type = check_content((*element)->content, *begin == *element);
	if (type == E_PIPE)
		return (processing_pipe(begin, element, data));
	if (type == E_REDIR_IN)
		return (processing_file(begin, element, *data, E_IN));
	if (type == E_REDIR_OUT)
		return (processing_file(begin, element, *data, E_OUT));
	if (type == E_INIT_PARAM)
		return (add_new_param(begin, element));
	return (KO);
}

/**
 * This function takes as input a linked list
 * of elements of type "t_list" and converts
 * it into a linked list of type "t_data"
 */

void	second_parser(t_list **begin, t_data *data)
{
	t_list	*element;

	element = *begin;
	while (element != NULL)
		if (processing_element(begin, &element, &data) == KO
			&& element != NULL)
			element = element->next;
	data->command = convert_list_to_array(*begin);
	data->param_list = g_common->new_list;
	g_common->new_list = NULL;
	if (*begin != NULL)
		remove_all_list(begin);
}
