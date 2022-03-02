/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:38:09 by stycho            #+#    #+#             */
/*   Updated: 2022/03/01 14:38:13 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//I'm sorry for that
void	choose_builtin(t_data *data, int flag, int pipe_flag);

/**
 * This function accepts a flag variable unique
 * to all builtins and executes the required builtin
 */

void	execute_builtin(t_data *data, int flag, int pipe_flag)
{
	t_pipeline_fds	yura_prosti;

	initialise_stdin_stdout(&yura_prosti);
	if (choose_output(&yura_prosti.fd_out, data->file) == -1)
	{
		reset_stdin_stdout(&yura_prosti);
		close(yura_prosti.fd_in);
		g_common->err_number = 1;
		return ;
	}
	choose_builtin(data, flag, pipe_flag);
	reset_stdin_stdout(&yura_prosti);
	close(yura_prosti.fd_in);
}

void	choose_builtin(t_data *data, int flag, int pipe_flag)
{
	if (flag == E_NOT_FUNCTION)
		return ;
	else if (flag == E_ENV)
		env();
	else if (flag == E_EXPORT)
		export(&data->command[1]);
	else if (flag == E_ECHO)
		echo(&data->command[1]);
	else if (flag == E_UNSET)
		unset(data->command);
	else if (flag == E_PWD)
		pwd();
	else if (flag == E_CD)
		cd(data->command[1]);
	else if (flag == E_EXIT)
	{
		if (data->command == NULL || data->command[1] == NULL)
			b_exit(g_common->err_number, pipe_flag);
		b_exit(ft_atoi(data->command[1]), pipe_flag);
	}
}
