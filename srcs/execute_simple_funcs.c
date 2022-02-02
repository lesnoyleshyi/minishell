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

void	ft_execute_cmd(char **cmd_w_args);

int	search_and_execute(char *cmd_w_args[])
{
	cmd_w_args = NULL;
	return (0);
}

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
	int		i;

	i = 0;
	cmd_data = command_list;
	reserved_stdin = dup(0);
	while (cmd_data != NULL && i < 4)
	{
//		printf("You have 20 sec to get info before %d pipe\n", i + 1);
//		printf("PID is %d\n\n", getpid());

		printf("The command to execute is %s\n", cmd_data->cmd_w_args[0]);
		sleep(3);
		pipe(pipe_fds);
//		printf("You have 20 sec to get info right after %d pipe\n", i + 1);
//		printf("PID is %d\n\n", getpid());
//		sleep(20);
		pid = fork();
//		printf("You have 20 sec to get info right after %d fork\n\n", i + 1);
//		sleep(20);
		//child
		if (pid == 0)
		{
//			printf("You have 20 sec to get info in child after %d fork\n", i + 1);
//			printf("pipe_fds[0] = %d\npipe_fds[1] = %d\n", pipe_fds[0], pipe_fds[1]);
//			printf("PID is %d\n\n", getpid());
			close(pipe_fds[0]);			//закрыли выход канала
			dup2(pipe_fds[1], 1);		//закрыли stdout, теперь пишет на вход пайпа
			close(pipe_fds[1]);			//наверное, можно закрыть просто 1 и ничего не поменяется
//			close(1);
//			sleep(20);
			ft_execute_cmd(cmd_data->cmd_w_args);
			printf("Exec failed\n");
//			sleep(1);
			exit(0);
		}
		//parent
		else
		{
			waitpid(pid, &exit_status, 0);
//			printf("%s has finished\n", cmd_data->cmd_w_args[0]);
//			printf("You have 20 sec to get info in parent after %d fork\n", i + 1);
//			printf("pipe_fds[0] = %d\npipe_fds[1] = %d\n", pipe_fds[0], pipe_fds[1]);
//			printf("PID is %d\n", getpid());
//			dup2(pipe_fds[0], 0);		//закрыли stdin, теперь читает из выхода пайпа
			close(pipe_fds[1]);
			if (cmd_data->next != NULL)
				dup2(pipe_fds[0], 0);
			else
			{
				while (read(pipe_fds[0], &buf, 1) == 1)
				{
					write(1, &buf, 1);
				}
//				dup2(pipe_fds[0], 1);
			}

//			dup2(pipe_fds[0], 0);


			close(pipe_fds[0]);
//			while (read(pipe_fds[0], &buf, 1) == 1)
//			{
//				write(1, &buf, 1);
//			}
//			printf("End of file in pipe found - nice!\n");
//			sleep(20);
			printf("%d\n\n", i);
			i++;
			cmd_data = cmd_data->next;
		}
	}
	printf("No more commands for today!\n");
//	while (read(0, &buf, 1) == 1)
//	{
//		write(1, &buf, 1);
//	}
//	printf("Yes, that's all\n");
	dup2(reserved_stdin, 0);
}

void	ft_execute_cmd(char **cmd_w_args)
{
	execlp(cmd_w_args[0], "kek", cmd_w_args[1], NULL);
}
