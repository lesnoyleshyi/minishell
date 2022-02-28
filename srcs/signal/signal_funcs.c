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

//It's here because readline.h doesn't contain this functions,
//whereas they are implemented
void	rl_replace_line (const char *text, int clear_undo);
int		rl_clear_visible_line (void);

//Handler for our program to mimic bash's behaviour on CTRL+\ and CTRL+C
void	main_handler(int signal);

void	clear_input()
{
	rl_on_new_line();
	rl_redisplay();
	write(2, "  \n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	do_nothing()
{
	rl_clear_visible_line();
	rl_on_new_line();
	rl_redisplay();
}

void	init_signal_handling(void (*handler)(int))
{
	struct sigaction sa;

	sa.sa_handler = handler;
	sigaction(SIGINT,  &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
//	sigaction(SIGTERM, &sa, NULL);
}

void	main_handler(int signal)
{
	if (signal == SIGINT)
		clear_input();
	if (signal == SIGQUIT)
		do_nothing();
}

void	child_handler(int signal)
{
	if (signal == SIGINT)
		SIG_DFL;
	if (signal == SIGQUIT)
		SIG_DFL;
	if (signal == SIGTERM)
		SIG_DFL;
}

void	redef_sigint_child(int signal)
{
	(void) signal;
	g_common->err_number = 130;
}
