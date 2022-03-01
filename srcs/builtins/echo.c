/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:04:16 by drayl             #+#    #+#             */
/*   Updated: 2022/02/23 13:04:18 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This function prints the passed arguments to standard output.
 */

void	echo(char **arg)
{
	int	n;

	n = 0;
	while (*arg != NULL && ft_strcmp(*arg, "-n") == 0)
	{
		n = 1;
		++arg;
	}
	while (*arg != NULL)
	{
		write(1, *arg, ft_strlen(*arg));
		if (**arg != '\0' && *(arg + 1) != NULL)
			write(1, " ", 1);
		++arg;
	}
	if (n == 0)
		write(1, "\n", 1);
	g_common->err_number = 0;
}
