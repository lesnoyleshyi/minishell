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

	child_ex_st = 0;
	//создаём пайп
	pipe(pipes_fds);
	pid = fork();
	//дочерний процесс
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		close(pipes_fds[0]);
		dup2(pipes_fds[1], 1);
		execlp("ls", "name1", "-lA", NULL);
	}
	//родительский процесс
	else
	{
		waitpid(pid, &child_ex_st, WNOHANG);

		printf("child ex_status: %d\n", child_ex_st);
		close(pipes_fds[1]);
		dup2(pipes_fds[0], 0);
		execlp("grep", "name2", "\\.", NULL);
	}
}

void	ft_execute_pipeline(t_s_cmd *command_list)
{
	int		pipe_fds[2];
	pid_t	pid;
	t_s_cmd	*cmd_data;
	int		exit_status;

	cmd_data = command_list;
	while (cmd_data->next != NULL)
	{
		pipe(pipe_fds);
		pid = fork();
		//child
		if (pid == 0)
		{
			close(pipe_fds[0]);			//закрыли выход канала
			dup2(pipe_fds[1], 1);		//закрыли stdout, теперь пишет на вход пайпа
			ft_execute_cmd(cmd_data->cmd_w_args);
		}
		//parent
		else
		{
			waitpid(pid, &exit_status, WNOHANG);
			dup2(pipe_fds[0], 0);		//закрыли stdin, теперь читает из выхода пайпа
			close(pipe_fds[1]);			//закрыли вход пайпа
			cmd_data = cmd_data->next;
		}
	}
}

void	ft_execute_cmd(char **cmd_w_args)
{
	execlp(cmd_w_args[0], "kek", cmd_w_args[1], NULL);
}
