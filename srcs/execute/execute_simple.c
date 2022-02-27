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
void	execute_simple(t_data *cmd_data);

//Performs redirections to mimic bash's side effects
//and create child process to return appropriate exit status.
//Exit status depends on redirections
//No error handling for fork(), because bash creates child processes
//in absolutely different manner (see make_child() function in jobs.c file).
void	execute_null_command(t_file *redir_list);

//Executes binary in subprocess by execve() call
//Creates char *env[] in function new_env
void	execute_binary(t_data *cmd_data);

void	execute_simple(t_data *cmd_data)
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
		execute_binary(cmd_data);
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
		g_common->err_number = get_child_exit_status(pid);
}

void	execute_binary(t_data *cmd_data)
{
	int	pid;
	int out_fd;
	int reserved_stdout;
	char **new_envp;

	reserved_stdout = dup(1);
	out_fd = 1;
	if (choose_output(&out_fd, cmd_data->file) != -1 && out_fd != 1)
		substitute_fd(out_fd, 1);
	pid = fork();
	if (pid == 0)
	{
		if (out_fd == -1)
			exit(EXIT_FAILURE);
		if (choose_inp_src(cmd_data->file) != 0)
			exit(EXIT_FAILURE);
		new_envp = new_env(cmd_data->param_list);
		ft_execve(cmd_data->command[0], cmd_data->command, new_envp);
	}
	else
	{
		substitute_fd(reserved_stdout, 1);
		g_common->err_number = get_child_exit_status(pid);
	}
}

//void	pipeline(t_data *command_list)
//{
//	execute_all_except_last(command_list);
//	execute_last(command_list);
//}
//
//void	execute_all_except_last(t_data *command_list)
//{
//	t_pipeline_fds	fds;
//	pid_t			pid;
//	t_data			*cur_cmd;
//
//	signal(SIGCHLD, SIG_IGN);
//	initialise_stdin_stdout(&fds);
//	cur_cmd = command_list;
//	while (cur_cmd != NULL && cur_cmd->next != NULL)
//	{
//		substitute_fd(fds.fd_in, 0);
//		if (do_piping(&fds, cur_cmd->command[0]) != 0)
//		{
//			cur_cmd = cur_cmd->next;
//			continue;
//		}
//		if (choose_output(&fds.fd_out, cur_cmd->file) != -1)
//			dup2(fds.fd_out, 1);
//		close(fds.fd_out);
//		pid = fork();
//		if (pid == 0)
//			execute_in_child(&fds, cur_cmd);
//		else
//			cur_cmd = cur_cmd->next;
//	}
//	substitute_fd(fds.fd_in, 0);
//}

