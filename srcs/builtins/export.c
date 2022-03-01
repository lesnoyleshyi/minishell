/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:17:29 by drayl             #+#    #+#             */
/*   Updated: 2022/02/23 13:17:31 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This function returns the element whose name is greater than the name
 * of the variable "limiter", but the minimum of the remaining
 */

static t_param	*get_min_param(t_param *limiter)
{
	t_param	*element;
	t_param	*min;

	element = g_common->env;
	min = NULL;
	while (element != NULL)
	{
		if (limiter != NULL && ft_strcmp(limiter->name, element->name) >= 0)
		{
			element = element->next;
			continue ;
		}
		if (min == NULL || ft_strcmp(min->name, element->name) > 0)
			min = element;
		element = element->next;
	}
	return (min);
}

/**
 * This function prints a sorted list of environment variables
 */

static void	print_export(void)
{
	t_param	*param;

	param = get_min_param(NULL);
	while (param != NULL)
	{
		if (param->value != NULL)
			printf("declare -x %s=\"%s\"\n", param->name, param->value);
		else
			printf("declare -x %s\n", param->name);
		param = get_min_param(param);
	}
}

/**
 * This function changes the field "value" in the variable "element"
 */

static void	export_env_param(t_param *element, t_param *param)
{
	if (param->value != NULL)
	{
		if (element->value != NULL)
			free(element->value);
		element->value = param->value;
	}
	param->value = NULL;
	destroy_param(&param);
}

/**
 * This function exports a value from a list of
 * local variables to a list of environment variables
 */

static void	export_local_param(t_param *element, t_param *param)
{
	if (param->value == NULL)
	{
		param->value = element->value;
		element->value = NULL;
	}
	add_param(&(g_common->env), param);
	delete_param(&(g_common->local_param), element);
}

/**
 * This function prints a sorted list of environment variables if no
 * parameters were passed, or exports the variable to the environment list.
 */

void	export(char **arg)
{
	t_param	*param;
	t_param	*element;
	int		flag;

	if (*arg == NULL)
	{
		print_export();
		return ;
	}
	if (check_valid_param_name(arg) != OK)
		return ;
	element = NULL;
	while (*arg != NULL)
	{
		param = init_param(*arg);
		flag = check_presence_param(&element, param->name);
		if (flag == NEW_PARAM)
			add_param(&(g_common->env), param);
		else if (flag == ENV_PARAM)
			export_env_param(element, param);
		else if (flag == LOCAL_PARAM)
			export_local_param(element, param);
		++arg;
	}
	g_common->err_number = 0;
}
