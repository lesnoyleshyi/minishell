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

//Changes old_output from pipe to output file or leaves it unchanged
//*
//It checks all files in redir_list consequently to mimic original bash's behaviour.
//*
//When it finds some problems with rw-permissions, it sets old_fd to -1 and returns -1.
//return (-1) helps to preserve dup2() in ft_execute_pipeline() from error.
//fd_out == -1 means we should exit(1) in child process in ft_execute_pipeline()
//*
int	ft_choose_output(int *old_output, t_file *redir_list);

//Checks whether list_of_all_redirections contains output redirections( >> or >)
//Returns 1 in case there is any
//Returns 0 in case there are no output redirections
int ft_is_here_output_redirections(t_file *list_of_all_redirections);

//Checks for reading permissions for filename
//*
//Returns 0 if read permissions OK,
//Returns 1 if read permissions not OK
//*
//I want to add checking for directory here later
int	ft_check_read_permissions(char *filename);

//Returns file descriptor of opened file if there is any of them in file_list
//Returns -2 if file_list is empty or doesn't contain any output files (> or >>)
//Returns -1 in case open() returns -1. It's an error indicator.
int	ft_open_output_files(t_file *redirect_list);

int	ft_choose_output(int *old_output, t_file *redir_list)
{
	t_file	*cur_file;

	cur_file = redir_list;
	while (cur_file != NULL)
	{
		if (cur_file->mod == E_IN && ft_check_read_permissions(cur_file->name) == 1)
		{
			close(*old_output);
			*old_output = -1;
			perror(cur_file->name);
			return (-1);
		}
		else if (cur_file->mod == E_OUT || cur_file->mod == E_APPEND)
		{
			close(*old_output);
			*old_output = ft_open_file(cur_file->name, cur_file->mod);
			if (*old_output == -1)
			{
				perror(cur_file->name);
				return (-1);
			}
		}
		cur_file = cur_file->next;
	}
	return (0);
}

int	ft_check_read_permissions(char *filename)
{
	if (access(filename, R_OK) == 1)
		return (1);
	return  (0);
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

int	ft_open_output_files(t_file *redirect_list)
{
	int		cur_fd;
	t_file	*cur_file;
	cur_fd = -2;
	cur_file = redirect_list;
	while (cur_file != NULL)
	{
		if (cur_file->mod == E_OUT || cur_file->mod == E_APPEND)
		{
			if (cur_fd != -2)
				close(cur_fd);
			cur_fd = ft_open_file(cur_file->name, cur_file->mod);
			if (cur_fd == -1)
				return (-1);
		}
		cur_file = cur_file->next;
	}
	return (cur_fd);
}