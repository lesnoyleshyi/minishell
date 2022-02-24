/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:34:47 by stycho            #+#    #+#             */
/*   Updated: 2022/02/23 14:34:49 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Executes builtin, binary or null-command
void	execute_simple(t_data *cmd_data, char *envp[]);

//Performs redirections to mimic bash's side effects
//and create child process to return appropriate exit status.
//Exit status depends on redirections
//No error handling for fork(), because bash creates child processes
//in absolutely different manner (see make_child() function in jobs.c file).
void	execute_null_command(t_file *redir_list);

//Executes binary in subprocess
void	execute_binary(t_data *cmd_data, char *envp[]);

void	execute_simple(t_data *cmd_data, char *envp[])
{
	int	builtin_type;

	if (cmd_data->command == NULL)
	{
		execute_null_command(cmd_data->file);
		return ;
	}
	builtin_type = check_function(cmd_data->command[0]);
	if (builtin_type != E_NOT_FUNCTION)
		execute_builtin(cmd_data, builtin_type);
	else
		execute_binary(cmd_data, envp);
}

void	execute_null_command(t_file *redir_list)
{
	pid_t	pid;
	int		stdout_copy;

	stdout_copy = 1;
	pid = fork();
	if (pid == 0)
	{
		if (choose_output(&stdout_copy, redir_list) == -1)
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}
	else
		g_common->err_number = ft_get_child_exit_status(pid);
}


// Посмотри нужен ли тебе ещё envp

void	execute_binary(t_data *cmd_data, char *envp[])
{
	int	pid;
	int out_fd;
	int reserved_output;
	char **new_envp;

	if (envp)
		;
	reserved_output = dup(1);
	out_fd = 1;
	if (choose_output(&out_fd, cmd_data->file) != -1)
		dup2(out_fd, 1);
	if (out_fd != 1)
		close(out_fd);
	pid = fork();
	if (pid == 0)
	{
		if (out_fd == -1)
			exit(EXIT_FAILURE);
		if (choose_inp_src(cmd_data->file) != 0)
			exit(EXIT_FAILURE);
		new_envp = new_env(cmd_data->param_list);
//		printf("%s\n", new_envp[0]);
		ft_execve(cmd_data->command[0], cmd_data->command, new_envp);
//		ft_execve(cmd_data->command[0], cmd_data->command, new_env(envp, cmd_data->param_list));
	}
	else
	{
		dup2(reserved_output, 1);
		close(reserved_output);
		g_common->err_number = ft_get_child_exit_status(pid);
	}
}
