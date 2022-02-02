/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_funcs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 21:20:38 by stycho            #+#    #+#             */
/*   Updated: 2022/01/28 21:20:41 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_apply_redirections_in(int pipe_input, int pipe_output, char *infile);

void	ft_execute_pipe()
{
	int 	pipes_fds[2];
	pid_t	pid;
	int		child_ex_st;

	child_ex_st = 1;
	pipe(pipes_fds);
	pid = fork();
	if (pid == -1)
		return ;
	//дочерний процесс
	if (pid == 0)
	{
		printf("Hello from 1 child process! Pipe read end is %d, write is %d\n", pipes_fds[0], pipes_fds[1]);
		printf("Child1 PID=%d\n", getpid());
		printf("Child1 PPID=%d\n", getppid());
		close(pipes_fds[0]);
		dup2(pipes_fds[1], 1);
		execlp("ls", "name1", "-lA", NULL);
	}
	//родительский процесс
	else
	{
		printf("first parent will wait %d\n", pid);
		waitpid(pid, &child_ex_st, 0);
		if (WIFEXITED(child_ex_st) == 0)
			printf("child1 ex_status: %d\n", child_ex_st);
		else
			printf("child1 ex_status: %d\n", WEXITSTATUS(child_ex_st));
		close(pipes_fds[1]);
		dup2(pipes_fds[0], 0);
		pipe(pipes_fds);
		pid = fork();
		if (pid == 0)
		{
			printf("Hello from second child process!\n");
			printf("Child2 PID=%d\n", getpid());
			printf("Child2 PPID=%d\n", getppid());
			close(pipes_fds[1]);
			dup2(pipes_fds[0], 0);
			execlp("cat", "name2", "-e", NULL);
		}
		else
		{
			printf("last parent will wait %d\n", pid);
			waitpid(pid, &child_ex_st, 0);
			if (WIFEXITED(child_ex_st) == 0)
				printf("child1 ex_status: %d\n", child_ex_st);
			else
				printf("child1 ex_status: %d\n", WEXITSTATUS(child_ex_st));
		}
	}
	printf("end of parent proc!\n");
}

void	ft_execute_pipeline(t_s_cmd *command_list)
{
	int		pipe_fds[2];
	pid_t	pid;
	t_s_cmd	*cmd_data;
	int		exit_status;
	char	buf;
	int		reserved_stdin;

	cmd_data = command_list;
	reserved_stdin = dup(0);
	while (cmd_data != NULL)
	{
		pipe(pipe_fds);
		pid = fork();
		if (pid == 0)
		{
			close(pipe_fds[0]);			//закрыли выход канала
			dup2(pipe_fds[1], 1);		//закрыли stdout, теперь пишет на вход пайпа
			close(pipe_fds[1]);			//можно закрыть просто 1 и ничего не поменяется
//			ft_apply_redirections_in(pipe_fds[1], pipe_fds[0], cmd_data->input);
			ft_execute_cmd(cmd_data->cmd_w_args);
			printf("Exec failed\n");
			exit(0);
		}
		else
		{
			waitpid(pid, &exit_status, 0);
			close(pipe_fds[1]);
			if (cmd_data->next != NULL)
				dup2(pipe_fds[0], 0);
			else
				while (read(pipe_fds[0], &buf, 1) == 1)
					write(1, &buf, 1);
			close(pipe_fds[0]);
			cmd_data = cmd_data->next;
		}
	}
	dup2(reserved_stdin, 0);
}

void	ft_execute_cmd(char *cmd_w_args[])
{
	if (ft_strchr(cmd_w_args[0], '/') == NULL)
	{
		printf("it is builtin!\n");
		ft_execute_builtin(cmd_w_args);
	}
	else
		execlp(cmd_w_args[0], "kek", cmd_w_args[1], NULL);
}

void	ft_apply_redirections_in(int pipe_input, int pipe_output, char *infile)
{
	int		inp_fd;
	char	*cur_dir;
	char	*full_path;

	close(pipe_output);
	if (ft_strchr(infile, '/') != NULL)
		inp_fd = open(infile, O_CREAT | O_TRUNC, 00644);
	else if (ft_strncmp(infile, "|", 1) == 0 || ft_strncmp(infile, "0", 1) == 0)
		inp_fd = 0;
	else
	{
		cur_dir = getcwd(NULL, 1);
		full_path = ft_strjoin(cur_dir, infile);
		inp_fd = open(full_path, O_CREAT | O_TRUNC, 00644);
		free(full_path);
		free(cur_dir);
	}
	dup2(inp_fd, 0);
	close(inp_fd);
	dup2(pipe_input, 1);
	close(pipe_input);
}

