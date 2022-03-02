/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:13:45 by stycho            #+#    #+#             */
/*   Updated: 2022/03/02 00:13:48 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_child_input(void);

void	child_quit(void);

void	child_handler(int signal)
{
	if (signal == SIGINT)
		clear_child_input();
	if (signal == SIGQUIT)
		child_quit();
	if (signal == SIGTERM)
		;
}

void	clear_child_input(void)
{
	int		exit_status;
	pid_t	pid;

	pid = waitpid(-1, &exit_status, 0);
	while (pid != -1)
		pid = waitpid(-1, &exit_status, 0);
	write(2, "\n", 1);
}

void	child_quit(void)
{
	int		exit_status;
	pid_t	pid;

	write(2, "Quit: ", 6);
	write(2, "3", 1);
	write(2, "\n", 1);
	pid = waitpid(-1, &exit_status, 0);
	while (pid != -1)
		pid = waitpid(-1, &exit_status, 0);
}
