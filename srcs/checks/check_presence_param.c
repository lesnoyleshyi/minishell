/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_presence_param.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 23:19:29 by drayl             #+#    #+#             */
/*   Updated: 2022/02/23 23:19:30 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This function checks if the shell variable list
 * or local variable list contains a variable with the given
 * "name", if so, the "element" pointer is set to that variable.
 */

int	check_presence_param(t_param **element, char *name)
{
	if (name == NULL)
		return (NEW_PARAM);
	*element = g_common->env;
	while (*element != NULL)
	{
		if (ft_strcmp((*element)->name, name) == 0)
			return (ENV_PARAM);
		*element = (*element)->next;
	}
	*element = g_common->local_param;
	while (*element != NULL)
	{
		if (ft_strcmp((*element)->name, name) == 0)
			return (LOCAL_PARAM);
		*element = (*element)->next;
	}
	return (NEW_PARAM);
}
