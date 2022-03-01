/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 23:07:30 by drayl             #+#    #+#             */
/*   Updated: 2022/02/23 23:07:38 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This function prints all values stored
 * in the global variable "g_common->env"
 */

void	env(void)
{
	t_param	*param;

	param = g_common->env;
	while (param != NULL)
	{
		if (param->value != NULL)
			printf("%s=%s\n", param->name, param->value);
		param = param->next;
	}
	g_common->err_number = 0;
}
