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

#include "../../includes/minishell.h"

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
		return (syntax_error(NEW_LINE));
	mod = get_mod_file(begin, element, mod);
	if (*element == NULL)
		return (syntax_error(NEW_LINE));
	if (check_content((*element)->content, FALSE) != E_NOT_SPEC_SYM)
		return (syntax_error((*element)->content));
	name = ft_strdup((*element)->content);
	if (name == NULL)
		memory_error();
	name = replace_all_param(name);
	remove_all_quote(name);
	file = init_new_file(name);
	if (file == NULL)
		memory_error();
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
		memory_error();
	if (param->name == NULL)
	{
		cmd_not_found(ft_strjoin("=", param->value));
		destroy_param(&param);
		return (SYNTAX_ERROR);
	}
	if (check_param_name(param->name) != '\0')
	{
		g_common->err_number = 258;
		return (SYNTAX_ERROR);
	}
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
		memory_error();
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

int	second_parser(t_list **begin, t_data *data)
{
	int		flag;
	t_list	*element;

	flag = OK;
	element = *begin;
	while (element != NULL && flag != SYNTAX_ERROR)
	{
		flag = processing_element(begin, &element, &data);
		if (flag == KO && element != NULL)
			element = element->next;
	}
	if (flag != SYNTAX_ERROR)
	{
		data->command = convert_list_to_array(*begin);
		data->param_list = g_common->new_list;
		g_common->new_list = NULL;
	}
	if (*begin != NULL)
		remove_all_list(begin);
	return (flag);
}
