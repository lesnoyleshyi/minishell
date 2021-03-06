/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:47:15 by drayl             #+#    #+#             */
/*   Updated: 2022/02/23 12:47:17 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This function prints the current directory
 */

void	pwd(void)
{
	printf("%s\n", g_common->pwd);
	g_common->err_number = 0;
}
