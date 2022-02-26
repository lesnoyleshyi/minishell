/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:33:13 by stycho            #+#    #+#             */
/*   Updated: 2022/02/21 13:33:14 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
void	rl_replace_line (const char *text, int clear_undo);

void	ft_clear_input(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(2, "  \n", 3);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void catch_child()
{
	int		exit_status;

	waitpid(-1, &exit_status, WNOHANG | WUNTRACED);
	g_common->err_number = WEXITSTATUS(exit_status);
	write(2, "z--\n", 4);
}

void catch_child2()
{
	int		exit_status;

	waitpid(-1, &exit_status, WNOHANG | WUNTRACED);
	g_common->err_number = WEXITSTATUS(exit_status);
	write(2, "z++\n", 4);
}

void	ft_wait(pid_t last_pid)
{
	pid_t	cur_pid;
	int		exit_status;

	cur_pid = waitpid(-1, &exit_status, 0);
	while (cur_pid != -1)
	{
		if (cur_pid == last_pid)
		{
			if (WEXITSTATUS(exit_status) == 0)
			{
				write(2, "ok\n", 3);
				g_common->err_number = 0;
			}
			else
			{
				write(2, "bad\n", 4);
				g_common->err_number = WEXITSTATUS(exit_status);
			}
		}
		else
			write(2, "z--\n", 4);
		cur_pid = waitpid(-1, &exit_status, 0);
	}
}
