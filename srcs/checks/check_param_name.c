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
	while (*str != '\0' && (*str == BOTTOM_LINE || ft_isalnum(*str) == 1))
		str++;
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
	{
		flag = check_param_name(*arg);
		if (flag != '\0' && flag != INIT_PARAM)
			printf("%s: syntax error near unexpected token \'%c\'\n", NAME, flag);
		++arg;
	}
	if (flag == '\0' || flag == INIT_PARAM)
		return (OK);
	return (KO);
}
