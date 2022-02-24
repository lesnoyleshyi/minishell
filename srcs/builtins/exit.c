/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:05:24 by stycho            #+#    #+#             */
/*   Updated: 2022/02/24 21:05:26 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	b_exit(int exit_status)
{
	write(2, "exit\n", 5);
	if (exit_status < 0 || exit_status > 255)
		exit(-1);
	exit(exit_status);
}
