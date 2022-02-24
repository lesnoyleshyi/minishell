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

void	ft_execute_in_child(t_pipeline_fds *pipe_fds_struct, t_data *cmd, char *envp[]);

int	execute_pipeline(t_data *command_list, char *envp[])
{
	t_pipeline_fds	fds;
	pid_t	pid;
	t_data	*cur_cmd;
	envp = NULL;
	signal(SIGCHLD, SIG_IGN);
	ft_initialise_stdin_stdout(&fds);
	cur_cmd = command_list;
	while (cur_cmd)
	{
//		ft_do_command;
		substitute_fd(fds.fd_in, 0);
		if (!cur_cmd->next && ft_make_last_cmd_redirs(&fds, cur_cmd->file) < 0)	//if it's the last command
			break ;
		else if (cur_cmd->next && ft_do_piping(&fds, cur_cmd->command[0]) != 0)	//it's not the last command in pipeline
			break ;
		if (choose_output(&fds.fd_out, cur_cmd->file) != -1)
			dup2(fds.fd_out, 1);
		close(fds.fd_out);														//I'm not sure if it's safe in case fd_out == 1 - maybe should be checked
		pid = fork();
		if (pid == 0)															//in child process
			ft_execute_in_child(&fds, cur_cmd, envp);
//		ft_clear_after_child();
		cur_cmd = cur_cmd->next;
	}
	ft_reset_stdin_stdout(&fds);
	return(get_child_exit_status(pid));
}

void	ft_execve(char *pathname, char *argv[], char *envp[])
{
	char	*abs_path;

	if (pathname == NULL)
		ft_execute_null_cmd();
	abs_path = get_abs_path_to_binary(pathname);
	if (is_directory(abs_path) == 1)
		custom_message_exit(pathname, CMD_IS_DIR, EXIT_COMMAND_IS_DIRECTORY);
	if (ft_strcmp("command not found", abs_path) == 0)
		custom_message_exit(pathname, CMD_NOT_FOUND, EXIT_COMMAND_NOT_FOUND);
	execve(abs_path, argv, envp);
	ft_perror_and_return(pathname, 1);
	exit(translate_errno_to_exit_status(errno));
}

int	ft_execute_null_cmd()
{
	exit(0);
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

void	ft_execute_in_child(t_pipeline_fds *pipe_fds_struct, t_data *cmd, char *envp[])
{
	if (pipe_fds_struct->fd_out == -1)
		exit(1);
	close(pipe_fds_struct->pipe_fds[0]);
	if (choose_inp_src(cmd->file) != 0)
		exit(1);
	ft_execve(cmd->command[0], cmd->command, envp);
}

void	execute(t_data *data, char *envp[])
{
	if (data == NULL)
		return ;
	if (data->next == NULL)
		execute_simple(data);
	else
		execute_pipeline(data, envp);
}
