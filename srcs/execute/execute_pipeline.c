/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:21:26 by stycho            #+#    #+#             */
/*   Updated: 2022/02/18 18:21:28 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "signal.h"

//Helps reduce lines of execute_pipeline() function
//We need quite a lot file descriptors for pipeline:
//reserved_stdin - to be able to reset stdin to default
// 		in case it's changed withing pipeline;
//reserved_stdout - the same as reserved_stdin;
//fd_in - temporary pointer to terminal's input, file or pipe;
//fd_out - temporary pointer to terminal's output, file or pipe.
void	initialise_stdin_stdout(t_pipeline_fds *pipe_fds_struct);

//Resets file descriptor 0 to terminal's input and
//file descriptor 1 to terminal's output
//after execution of all commands in pipeline.
//It also closes unnecessary file descriptors
//for reserved input and output.
void	reset_stdin_stdout(t_pipeline_fds *pipe_fds_struct);

//Executes commands connected with pipes
void	execute_pipeline(t_data *command_list);

//Does all necessary stuff in child process:
//closes pipe's output,
//exits with error status 1 if redirections fails or 0 in case null command,
//executes builtin or binary and exits with appropriate exit status.
void	execute_in_child(t_pipeline_fds *pipe_fds_struct, t_data *cmd);

//Waits for all child processes to avoid zombie creation
//Changes global variable "err_number" if catches SIGCHILD
//from process denoted by last_pid.
void	ft_wait(pid_t last_pid);

void	execute_pipeline(t_data *command_list)
{
	t_pipeline_fds	fds;
	pid_t			pid;
	t_data			*cur_cmd;

	initialise_stdin_stdout(&fds);
	cur_cmd = command_list;
	while (cur_cmd)
	{
		substitute_fd(fds.fd_in, 0);
		if (!cur_cmd->next && do_last_cmd_redirs(&fds, cur_cmd->file, &pid) < 0)
			break ;
		else if (cur_cmd->next != NULL)
			do_piping(&fds, cur_cmd->command[0]);
		if (choose_output(&fds.fd_out, cur_cmd->file) != -1)
			dup2(fds.fd_out, 1);
		close(fds.fd_out);
		init_signal_handling(child_handler);
		pid = fork();
		if (pid == 0)
			execute_in_child(&fds, cur_cmd);
		cur_cmd = cur_cmd->next;
	}
	reset_stdin_stdout(&fds);
	ft_wait(pid);
}

void	execute_in_child(t_pipeline_fds *pipe_fds_struct, t_data *cmd)
{
	int		builtin_type;
	char	**new_envp;

	close(pipe_fds_struct->pipe_fds[0]);
	if (pipe_fds_struct->fd_out == -1 || choose_inp_src(cmd->file) != 0)
		exit(1);
	if (cmd->command == NULL)
		exit(0);
	builtin_type = is_builtin(cmd->command[0]);
	if (builtin_type != E_NOT_FUNCTION)
	{
		execute_builtin(cmd, builtin_type, WITHIN_PIPELINE);
		exit(g_common->err_number);
	}
	new_envp = new_env(cmd->param_list);
	ft_execve(cmd->command[0], cmd->command, new_envp);
}

void	initialise_stdin_stdout(t_pipeline_fds *pipe_fds_struct)
{
	pipe_fds_struct->reserved_stdin = dup(0);
	pipe_fds_struct->reserved_stdout = dup(1);
	pipe_fds_struct->fd_in = dup(0);
	pipe_fds_struct->fd_out = 1;
}

void	reset_stdin_stdout(t_pipeline_fds *pipe_fds_struct)
{
	dup2(pipe_fds_struct->reserved_stdin, 0);
	dup2(pipe_fds_struct->reserved_stdout, 1);
	close(pipe_fds_struct->reserved_stdin);
	close(pipe_fds_struct->reserved_stdout);
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
