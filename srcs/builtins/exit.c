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

void	b_exit(int exit_status, int pipe_flag)
{
	if (pipe_flag == 0)
		write(2, "exit\n", 5);
	exit(exit_status);
}
