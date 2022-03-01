/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 23:16:12 by drayl             #+#    #+#             */
/*   Updated: 2022/02/23 23:16:14 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This function returns the first character after the parameter name.
 * If character is not equal to "INIT_PARAM" or '\0' hence syntax error
 */

char	check_param_name(char *str)
{
	while (*str != '\0' && (*str == BOTTOM_LINE || ft_isalnum(*str) == TRUE))
		str++;
	if (*str == INIT_PARAM || *str == '\0')
		return (*str);
	put_error_param_name(*str);
	return (*str);
}

/**
 * This function takes a list of strings listing parameters or
 * parameter initializations and checks all parameter names for validity
 */

int	check_valid_param_name(char **arg)
{
	char	flag;

	flag = '\0';
	while (*arg != NULL && (flag == '\0' || flag == INIT_PARAM))
		flag = check_param_name(*(arg++));
	if (flag == '\0' || flag == INIT_PARAM)
		return (OK);
	return (KO);
}

/**
 * This function assumes an environment
 * specifically for the "unset" builtin
 */

int	check_param_name_for_unset(char **arg)
{
	char	flag;

	if (*arg == NULL)
		return (KO);
	while (*arg != NULL)
	{
		flag = check_param_name(*arg);
		if (flag != '\0')
			break;
		++arg;
	}
	if (flag == '\0')
		return (OK);
	if (flag == INIT_PARAM)
		put_error_id_for_unset(*arg);
	return (KO);
}
