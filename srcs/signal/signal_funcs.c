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
#include <signal.h>

//It's here because readline's header doesn't work without it
void	rl_replace_line (const char *text, int clear_undo);

void	signal_handler(int signal);

void	clear_input()
{
	rl_on_new_line();
	rl_redisplay();
	write(2, "  \n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_wait(pid_t last_pid)
{
	pid_t	cur_pid;
	int		exit_status;

	cur_pid = waitpid(-1, &exit_status, 0);
	while (cur_pid != -1)
	{
		if (cur_pid == last_pid)
			g_common->err_number = WEXITSTATUS(exit_status);
		cur_pid = waitpid(-1, &exit_status, 0);
	}
}

void	init_signal_handling()
{
	struct sigaction sa;

	sa.sa_handler = signal_handler;
//	sa.sa_handler = SIG_IGN;
//	sigemptyset(&sa.sa_mask);
//	sa.sa_flags = 0;

//	sigaction(SIGINT,  &signal_handler, NULL);
//	sigaction(SIGQUIT, &signal_handler, NULL);

	sigaction(SIGINT,  &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
//	sigaction(SIGPIPE, &sa, NULL);
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
		clear_input();
	if (signal == SIGQUIT)
		;
//	if (signal == SIGPIPE)
//		exit(0);
}
