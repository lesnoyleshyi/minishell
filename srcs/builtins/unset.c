/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 23:10:02 by drayl             #+#    #+#             */
/*   Updated: 2022/02/23 23:10:04 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This function removes environment variables or local variables
 * whose names are specified in the passed array of strings "arg"
 */

void	unset(char **arg)
{
	int		flag;
	t_param	*param;

	if (check_param_name_for_unset(arg) != OK)
		return ;
	param = NULL;
	while (*arg != NULL)
	{
		flag = check_presence_param(&param, *arg);
		if (flag == ENV_PARAM)
			delete_param(&g_common->env, param);
		else if (flag == LOCAL_PARAM)
			delete_param(&g_common->local_param, param);
		++arg;
	}
	g_common->err_number = 0;
}
