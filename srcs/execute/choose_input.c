/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:44:03 by stycho            #+#    #+#             */
/*   Updated: 2022/02/18 20:44:04 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "fcntl.h"
//Opens file referenced by filename, no matter where this file is located
int	ft_open_file(char *filename, int mode_for_open);

//We'll receive full string that parser expands from heredoc, not pathname.
//This function creates pipe or temporary file that'll contain this string.
//Decision about storage rely on len(heredoc_string) and max size of pipe.
int	ft_heredoc_to_fd(char *heredoc_string);

//Checks whether list_of_all_redirections contains output redirections( >> or >)
//Returns 1 in case there is any
//Returns 0 in case there are no output redirections
int ft_is_here_output_redirections(t_file *list_of_all_redirections);

//Returns file descriptor of opened file if there is any of them in file_list
//Returns -2 if file_list is empty or doesn't contain any output files (> or >>)
//Returns -1 in case open() returns -1. It's an error indicator.
int	ft_open_output_files(t_file *redirect_list);

//Changes input_source from previous (could be stdin or pipe's output) to output
//file/heredoc if there is any in redirect_list
//*
//Closes previous input fd only if it finds any input redirection in redirect_list
//*
//Returns -1 in case of error
//Opens input files(< or <<stop_word) in cycle if there are some.
//Leaves only the last opened, close other ones.
//
int	ft_choose_inp_src(t_file *redirect_list);

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

int	ft_open_file(char *filename, int mode_for_open)
{
	int		fd;
//	int		oflag;

	if (mode_for_open == E_APPEND)
	{
//		oflag = O_WRONLY | O_CREAT | O_APPEND;
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 00644);
	}
	else if (mode_for_open == E_OUT)
	{
//		oflag = O_WRONLY | O_CREAT | O_TRUNC;
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	}
	else if (mode_for_open == E_IN)
	{
		fd = open(filename, O_RDONLY);
	}
	else if (mode_for_open == E_HEREDOC)
	{
		fd = ft_heredoc_to_fd(filename);
	}
	else
	{
//		oflag = 0;
		return (-1);
	}

	return (fd);
}

int	ft_choose_inp_src(t_file *redirect_list)
{
	t_file	*cur_file;
	int		input_fd;

	input_fd = 0;
	cur_file = redirect_list;
	while (cur_file != NULL)
	{
		if (cur_file->mod == E_IN || cur_file->mod == E_HEREDOC)
		{
			close(input_fd);
			input_fd = ft_open_file(cur_file->name, cur_file->mod);
			if (input_fd == -1)
				break;
		}
		cur_file = cur_file->next;
	}
	if (input_fd == -1)
	{
		perror(cur_file->name);
		return (-1);
	}
	dup2(input_fd, 0);
	if (input_fd != 0)
		close(input_fd);
	return (0);
}

int ft_heredoc_to_fd(char *string)
{
	if (string)
		return (0);
	else
		return (1);
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