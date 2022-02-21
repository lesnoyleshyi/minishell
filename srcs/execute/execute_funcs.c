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

int	ft_open_output_files(t_file *file_list);

//Opens input files(< or <<stop_word) in cycle if there are some.
//Leaves only the last opened, close other ones.
//
int	ft_choose_inp_src(t_file *redirect_list, int old_input_fd);

int	ft_execute_pipeline(t_data *command_list, char *envp[])
{
	int		reserved_stdin;
	int		reserved_stdout;
	int		fd_in;
	int		fd_out;
	pid_t	pid;
	t_data	*curr_cmd;
	int		pipe_fds[2];

	envp = NULL;
	reserved_stdin = dup(0);
	reserved_stdout = dup(1);
	signal(SIGCHLD, SIG_IGN);

	fd_in = dup(0);
	curr_cmd = command_list;
	while (curr_cmd)
	{
//		fd_in = ft_choose_inp_src(curr_cmd->file, fd_in);
//		if (fd_in == -1)
//			write(2, "ft_choose_inp_src returns -1\n", 30);
		dup2(fd_in, 0);
		close(fd_in);
		if (curr_cmd->next == NULL)												//if it's the last command
		{
			if (ft_is_here_output_redirections(curr_cmd->file) == 1)			//if last simple command has output redirection
			{
				write(2, "has output redirection\n", 24);
				fd_out = ft_open_output_files(curr_cmd->file);					//we should open all "output files" in list of files to be opened, and leave only the last file opened
				if (fd_out == -1)
				{
					write(2, "ft_open_output_files returned -1\n", 34);
					g_common->err_number = -1;
					break;
				}
			}
			else																//if last simple command doesn't have output redirection
				fd_out = dup(reserved_stdout);									//we should restore stdout, because it might be changed inside while loop
		}
		else																	//it's not the last command in pipeline
		{
			pipe(pipe_fds);
			fd_out = pipe_fds[1];												//we'll redirect output to pipe's input
			fd_in = pipe_fds[0];												//and read from pipe's output
		}
		if (ft_choose_output(&fd_out, curr_cmd->file) != -1)
			dup2(fd_out, 1);													//fd==1 now points to fd_out - depends on next: it's the last command(reserved stdout or file) or not (pipe's input)
		close(fd_out);															//I'm not sure if it's safe in case fd_out == 1 - maybe should be checked
		pid = fork();
		if (pid == 0)															//in child process
		{
			if (fd_out == -1)
				exit(1);
//			env = ft_update_env();
//			close(pipe_fds[0]);
			execve(curr_cmd->command[0], curr_cmd->command, NULL);
			perror("execve");
			exit(1);
		}
//		ft_reset_env();
		curr_cmd = curr_cmd->next;
	}
	dup2(reserved_stdin, 0);
	dup2(reserved_stdout, 1);
	close(reserved_stdin);
	close(reserved_stdout);
	return(ft_get_child_exit_status(pid));
}

int	ft_get_child_exit_status(pid_t pid)
{
	int exit_status;

	waitpid(pid, &exit_status, 0);
	if (WEXITSTATUS(exit_status) == 0)
		return (0);
	else
		return (WEXITSTATUS(exit_status));
//		here we (theoretically) can catch different ex_st in case of signal termination
}


