/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 23:13:22 by drayl             #+#    #+#             */
/*   Updated: 2022/02/23 23:13:23 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This delete function checks if all fields of the global
 * variable "g_common" have been correctly initialized.
 * Returns "TRUE" if at least one field is not initialized correctly
 */

int	check_common(void)
{
	return (g_common->env == NULL || g_common->home == NULL
		|| g_common->history_file == NULL || g_common->pwd == NULL);
}
