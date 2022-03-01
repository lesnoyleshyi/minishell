/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:07:38 by stycho            #+#    #+#             */
/*   Updated: 2022/03/01 15:07:40 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Creates pipe inside itself and make
//fd_in points to pipe's input
//fd_out points to pipe's output
//*
//It do the next, but with structure fields
//
//	pipe(pipe_fds);
//	fd_in = pipe_fds[0];
//	fd_out = pipe_fds[1];
//
int	do_piping(t_pipeline_fds *pipe_fds_struct, char *cmd_name);

//Closes old_fd and makes new_fd points to the source of old_fd
//Returns 0 on success
//Returns -1 on failure
int	substitute_fd(int old_fd, int new_fd);

int	do_piping(t_pipeline_fds *pipe_fds_struct, char *cmd_name)
{
	if (pipe(pipe_fds_struct->pipe_fds) == -1)
		return (perror_and_return(cmd_name, errno));
	pipe_fds_struct->fd_in = pipe_fds_struct->pipe_fds[0];
	pipe_fds_struct->fd_out = pipe_fds_struct->pipe_fds[1];
	return (0);
}

int	substitute_fd(int old_fd, int new_fd)
{
	int	ret_val;

	ret_val = 0;
	if (dup2(old_fd, new_fd) == -1)
		ret_val = -1;
	if (close(old_fd) == -1)
		ret_val = -1;
	return (ret_val);
}
