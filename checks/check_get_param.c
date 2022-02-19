/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_get_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 00:12:28 by drayl             #+#    #+#             */
/*   Updated: 2022/02/20 00:12:30 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * This function checks if a string contains
 * a variable. If yes, the function returns
 * the index of the beginning of the
 * variable name. If not, "-1" is returned.
 */

int	check_get_param(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		if (str[i++] == GET_PARAM)
			return (i);
	return (FALSE);
}
