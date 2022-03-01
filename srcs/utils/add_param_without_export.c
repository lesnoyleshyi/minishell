/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_param_without_export.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:39:48 by stycho            #+#    #+#             */
/*   Updated: 2022/03/01 14:39:49 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_param	*get_param_from_list(t_param **begin, t_param **element)
{
	t_param	*param;
	t_param	*res;

	if (*begin == *element)
	{
		*begin = (*begin)->next;
		param = *element;
		*element = (*element)->next;
		return (param);
	}
	param = *begin;
	while (param != NULL && param->next != *element)
		param = param->next;
	if (param == NULL)
		return (NULL);
	param->next = (*element)->next;
	(*element)->next = NULL;
	res = *element;
	*element = param->next;
	return (res);
}

static void	pop_element(t_param **element)
{
	t_param	*next;

	next = (*element)->next;
	free((*element)->name);
	free(*element);
	*element = next;
}

void	add_param_without_export(t_param **begin)
{
	int		flag;
	t_param	*param;
	t_param	*element;

	element = *begin;
	while (element != NULL)
	{
		flag = check_presence_param(&param, element->name);
		if (flag == NEW_PARAM)
		{
			param = get_param_from_list(begin, &element);
			add_param(&g_common->local_param, param);
		}
		else
		{
			if (param->value != NULL)
				free(param->value);
			param->value = element->value;
			element->value = NULL;
			pop_element(&element);
		}
	}
}
