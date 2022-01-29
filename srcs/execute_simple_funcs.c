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

int	search_and_execute(char *cmd_w_args[])
{
	cmd_w_args = NULL;
	return (0);
}

void	ft_execute_pipeline()
{
	int 	pipes_fds[2];
	pid_t	pid;
	int		child_ex_st;

	//создаём пайп
	pipe(pipes_fds);

	pid = fork();
	//дочерний процесс
	if (pid == 0)
	{
		close(pipes_fds[0]);
		dup2(pipes_fds[1], 1);
		execlp("ls", "name1", "-lA", NULL);
		exit(0);
	}
	//родительский процесс
	else
	{
		waitpid(pid, &child_ex_st, WNOHANG);
		dup2(pipes_fds[0], 0);
		close(pipes_fds[1]);
		execlp("wc", "name2", "-l", NULL);
	}
}
