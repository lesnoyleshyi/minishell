/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:43:55 by stycho            #+#    #+#             */
/*   Updated: 2022/02/21 14:43:56 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "errno.h"

//Changes old_output to output file or leaves it unchanged
//*
//It checks all files in redir_list consequently to mimic
//original bash's behaviour.
//*
//When it finds some problems with rw-permissions,
//it sets old_fd to -1 and returns -1.
//return (-1) helps to preserve dup2() in ft_execute_pipeline() from error.
//fd_out == -1 means we should exit(1) in child process in ft_execute_pipeline()
//*
int	choose_output(int *old_output, t_file *redir_list);

//Checks whether list_of_all_redirections contains output redirections( >> or >)
//Returns 1 in case there is any
//Returns 0 in case there are no output redirections
int	is_here_output_redirections(t_file *list_of_all_redirections);

//Checks for reading permissions for filename
//*
//Returns 0 if read permissions OK,
//Returns 1 if read permissions not OK
//*
//I want to add checking for directory here later
int	check_read_perm(char *filename);

//Perform required redirections to redirects command's output to
//a) file - if ft_is_here... finds any output redirection
//b) stdout - if no > or >> redirections are in redir_list
//*
//Returns -1 if there is any error with any file from redir_list
//Returns 0 on success
int	do_last_cmd_redirs(t_pipeline_fds *fds_s, t_file *redir_list, pid_t *pid);

int	choose_output(int *old_output, t_file *redir_list)
{
	t_file	*cur_file;

	cur_file = redir_list;
	while (cur_file != NULL)
	{
		if (cur_file->mod == E_IN && check_read_perm(cur_file->name) == -1)
		{
			close(*old_output);
			*old_output = -1;
			return (perror_and_return(cur_file->name, -1));
		}
		else if (cur_file->mod == E_OUT || cur_file->mod == E_APPEND)
		{
			close(*old_output);
			*old_output = ft_open_file(cur_file->name, cur_file->mod);
			if (*old_output == -1)
				return (perror_and_return(cur_file->name, -1));
		}
		cur_file = cur_file->next;
	}
	return (0);
}

int	check_read_perm(char *filename)
{
	if (access(filename, R_OK) == -1)
		return (-1);
	return (0);
}

int	is_here_output_redirections(t_file *list_of_all_redirections)
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

int	do_last_cmd_redirs(t_pipeline_fds *fds_s, t_file *redir_list, pid_t *pid)
{
	if (is_here_output_redirections(redir_list) == 1)
	{
		if (choose_output(&fds_s->fd_out, redir_list) == -1)
		{
			*pid = fork();
			if (*pid == 0)
				exit(1);
			else
				return (-1);
		}
	}
	else
		fds_s->fd_out = dup(fds_s->reserved_stdout);
	return (0);
}
