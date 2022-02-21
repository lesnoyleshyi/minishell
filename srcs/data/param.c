/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 00:06:39 by drayl             #+#    #+#             */
/*   Updated: 2022/02/20 00:06:41 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This function creates a new element of type "t_param"
 * and places it at the end of the list "begin"
 */

void	add_param(t_param **begin, t_param *new)
{
	t_param	*element;

	if (begin == NULL || *begin == NULL)
	{
		*begin = new;
		return ;
	}
	element = *begin;
	while (element->next != NULL && ft_strcmp(element->name, new->name))
		element = element->next;
	element->next = new;
}

/**
 * This function finds the required
 * element in the list and removes it.
 */

void	delete_param(t_param **begin, t_param *element)
{
	t_param	*param;

	if (*begin == element)
		*begin = element->next;
	else
	{
		param = *begin;
		while (param != NULL && param->next != element)
			param = param->next;
		if (param != NULL)
			param->next = element->next;
	}
	if (element->name != NULL)
		free(element->name);
	if (element->value != NULL)
		free(element->value);
	free(element);
}

/**
 * This function takes a string like "NAME=VALUE",
 * creates a new element of type t_param and returns it.
 * In case of an error, it returns NULL
 */

t_param	*init_param(const char *str)
{
	t_param	*new;
	size_t	index;

	new = (t_param *) malloc(sizeof (t_param));
	if (new == NULL)
		return (NULL);
	index = 0;
	while (str[index] != INIT_PARAM)
		++index;
	new->name = get_substr(str, 0, index);
	new->value = get_substr(str, index + 1, ft_strlen(str));
	new->app = FALSE;
	new->value = replace_all_param(new->value);
	remove_all_quote(new->value);
	new->next = NULL;
	if (new->name != NULL && *new->name == '\0')
		new->name = remove_string(new->name);
	if (new->value != NULL && *new->value == '\0')
		new->value = remove_string(new->value);
	return (new);
}

/**
 * This function removes the entire list of type "t_param"
 */

void	destroy_param(t_param **begin)
{
	t_param	*element;

	if (begin == NULL)
		return ;
	while (*begin)
	{
		element = (*begin)->next;
		if ((*begin)->name != NULL)
			free((*begin)->name);
		if ((*begin)->value != NULL)
			free((*begin)->value);
		free(*begin);
		*begin = element;
	}
}

/**
 * This function looks up a variable by name in
 * the list: "env" and "local_param" and returns
 * its "value". Returns NULL if a variable with
 * the same name does not exist.
 */

char	*get_param_value(const char *name)
{
	t_param	*param;

	param = g_common->env;
	if (ft_strcmp(name, "?") == 0)
		return (ft_itoa(g_common->err_number));
	while (param != NULL)
	{
		if (ft_strcmp(param->name, name) == 0)
			return (param->value);
		param = param->next;
	}
	param = g_common->local_param;
	while (param != NULL)
	{
		if (ft_strcmp(param->name, name) == 0)
			return (param->value);
		param = param->next;
	}
	return (NULL);
}
