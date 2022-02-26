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
#include "errno.h"
#include "signal.h"

int	ft_open_output_files(t_file *file_list);

//Do nothing but exit(0)
int	ft_execute_null_cmd();

//Expand pathname and call execve() on it
void	ft_execve(char *pathname, char *argv[], char *envp[]);

//Helps reduce lines of ft_execute_pipeline
//*
void	ft_initialise_stdin_stdout(t_pipeline_fds *pipe_fds_struct);

//Resets stdin to 0 and stdout to 1 after execution command
void	ft_reset_stdin_stdout(t_pipeline_fds *pipe_fds_struct);

void	execute_in_child(t_pipeline_fds *pipe_fds_struct, t_data *cmd);

void	execute(t_data *data)
{
	if (data == NULL)
		return ;
	if (data->next == NULL)
		execute_simple(data);
	else
		execute_pipeline(data);
}

int	execute_pipeline(t_data *command_list)
{
	t_pipeline_fds	fds;
	pid_t			pid;
	t_data			*cur_cmd;

	ft_initialise_stdin_stdout(&fds);
	cur_cmd = command_list;
	while (cur_cmd)
	{
		substitute_fd(fds.fd_in, 0);
		if (!cur_cmd->next && ft_make_last_cmd_redirs(&fds, cur_cmd->file) < 0)	//if it's the last command
			break ;
		else if (cur_cmd->next && ft_do_piping(&fds, cur_cmd->command[0]) != 0)	//it's not the last command in pipeline
		{
			cur_cmd = cur_cmd->next;
			continue;
		}
		if (choose_output(&fds.fd_out, cur_cmd->file) != -1)
			dup2(fds.fd_out, 1);
		close(fds.fd_out);														//I'm not sure if it's safe in case fd_out == 1 - maybe should be checked
		pid = fork();
		if (pid == 0)															//in child process
			execute_in_child(&fds, cur_cmd);
		cur_cmd = cur_cmd->next;
	}
	printf("\n %d\n", pid);
	ft_wait(pid);
	ft_reset_stdin_stdout(&fds);
	return(13);
}

void	ft_initialise_stdin_stdout(t_pipeline_fds *pipe_fds_struct)
{
	pipe_fds_struct->reserved_stdin = dup(0);
	pipe_fds_struct->reserved_stdout = dup(1);
	pipe_fds_struct->fd_in = dup(0);
	pipe_fds_struct->fd_out = 1;
}

void	ft_reset_stdin_stdout(t_pipeline_fds *pipe_fds_struct)
{
	dup2(pipe_fds_struct->reserved_stdin, 0);
	dup2(pipe_fds_struct->reserved_stdout, 1);
	close(pipe_fds_struct->reserved_stdin);
	close(pipe_fds_struct->reserved_stdout);
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
	builtin_type = check_function(cmd->command[0]);
	if (builtin_type != E_NOT_FUNCTION)
	{
		execute_builtin(cmd, builtin_type);
		exit(g_common->err_number);
	}
	new_envp = new_env(cmd->param_list);
	ft_execve(cmd->command[0], cmd->command, new_envp);
}

void	ft_execve(char *pathname, char *argv[], char *envp[])
{
	char	*abs_path;

//	errno = 0;
	if (pathname == NULL)
		exit(0);
	abs_path = get_abs_path_to_binary(pathname);
	if (is_directory(abs_path) == 1)
		custom_message_exit(pathname, CMD_IS_DIR, EXIT_COMMAND_IS_DIRECTORY);
	if (ft_strcmp("command not found", abs_path) == 0)
		custom_message_exit(pathname, CMD_NOT_FOUND, EXIT_COMMAND_NOT_FOUND);
	execve(abs_path, argv, envp);
	ft_perror_and_return(pathname, 1);
	exit(translate_errno_to_exit_status(errno));
}
