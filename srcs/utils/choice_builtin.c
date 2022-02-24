/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choice_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 05:48:10 by drayl             #+#    #+#             */
/*   Updated: 2022/02/24 05:48:12 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This function accepts a flag variable unique
 * to all builtins and executes the required builtin
 */

void	choice_builtin(t_data *data, int flag)
{
	if (flag == E_NOT_FUNCTION)
		return ;
	else if (flag == E_ENV)
		env();
	else if (flag == E_EXPORT)
		export(&data->command[1]);
	else if (flag == E_ECHO)
		echo(&data->command[1]);
	else if (flag == E_UNSET)
		unset(data->command);
	else if (flag == E_PWD)
		pwd();
	else if (flag == E_CD)
		cd(data->command[1]);
}
