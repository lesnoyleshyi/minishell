/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 00:12:19 by drayl             #+#    #+#             */
/*   Updated: 2022/02/20 00:12:21 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * This function checks if we have implemented
 * the given "function". If yes, the function
 * will return the function ID. If not,
 * the function will return "NOT_FUNCTION"
 */

int	check_function(const char *function)
{
	if (ft_strcmp(function, C_CD))
		return (E_CD);
	if (ft_strcmp(function, C_ECHO))
		return (E_ECHO);
	if (ft_strcmp(function, C_ENV))
		return (E_ENV);
	if (ft_strcmp(function, C_EXIT))
		return (E_EXIT);
	if (ft_strcmp(function, C_EXPORT))
		return (E_EXPORT);
	if (ft_strcmp(function, C_PWD))
		return (E_PWD);
	if (ft_strcmp(function, C_UNSET))
		return (E_UNSET);
	return (E_NOT_FUNCTION);
}
