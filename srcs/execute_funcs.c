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

#include "minishell.h"

int	ft_open_output_files(t_file *file_list);

//Checks whether list_of_all_redirections contains output redirections( >> or >)
//Returns 1 in case there is any
//Returns 0 in case there are no output redirections
int ft_is_here_output_redirections(t_file *list_of_all_redirections);

//void	ft_zombie_killer(int signal_number);

int	execute(t_data *command_list, char *envp[])
{
	int		reserved_stdin;
	int		reserved_stdout;
	int		fd_in;
	int		fd_out;
	pid_t	pid;
	t_data	*curr_cmd;
	int		pipe_fds[2];
	int		i;
//	pid_t

	envp = NULL;
	reserved_stdin = dup(0);
	reserved_stdout = dup(1);
	signal(SIGCHLD, SIG_IGN);

	i = 0;
	fd_in = dup(0);
	curr_cmd = command_list;
	while (curr_cmd)
	{
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
					last_command_exit_value = -1;
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
		dup2(fd_out, 1);														//fd==1 now points to fd_out - depends on next: it's the last command(reserved stdout or file) or not (pipe's input)
		close(fd_out);															//I'm not sure if it's safe in case fd_out == 1 - maybe should be checked
		pid = fork();
		if (pid == 0)															//in child process
		{
//			env = ft_update_env();
			close(pipe_fds[0]);
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

int ft_is_here_output_redirections(t_file *list_of_all_redirections)
{
	t_file	*cur_redirection;

	cur_redirection = list_of_all_redirections;
	while (cur_redirection != NULL)
	{
		if (cur_redirection->mod == E_APPEND || cur_redirection->mod == E_OUT)
			return (1);
		cur_redirection = cur_redirection->next;
	}
	return (0);
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

//void	ft_zombie_killer(int signal_number)
//{
//
//	wait(NULL);
//}

