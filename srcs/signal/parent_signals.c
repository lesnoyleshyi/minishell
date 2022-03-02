/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:16:25 by stycho            #+#    #+#             */
/*   Updated: 2022/03/02 00:16:26 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//We should use rl_clear_visible_line() here, but subject restrict it.
void	do_nothing(void);

//It's one more dummy function that we hadn't to create
//if we were able to redefine readline's behaviour on signal catching.
void	clear_input(void);

void	main_handler(int signal)
{
	if (signal == SIGINT)
		clear_input();
	if (signal == SIGQUIT)
		do_nothing();
}

void	do_nothing(void)
{
	rl_on_new_line();
	rl_redisplay();
}

void	clear_input(void)
{
	rl_on_new_line();
	rl_redisplay();
	write(2, "  \n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
