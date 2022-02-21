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

//Returns file descriptor of opened file if there is any of them in file_list
//Returns -2 if file_list is empty or doesn't contain any output files (> or >>)
//Returns -1 in case open() returns -1. It's an error indicator.
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

int	ft_choose_inp_src(t_file *redirect_list, int old_input_fd)
{
	int		new_input_fd;
	t_file	*cur_file;

	write(2, "ft_choose_inp_src\n", 19);
	new_input_fd = -2;
	cur_file = redirect_list;
	while (cur_file != NULL)
	{
		if (cur_file->mod == E_IN || cur_file->mod == E_HEREDOC)
		{
			if (new_input_fd != -2)
				close(new_input_fd);
			new_input_fd = ft_open_file(cur_file->name, cur_file->mod);
			if (new_input_fd == -1)
				return (-1);
			write(2, "+1 opened file\n", 16);
		}
		write(2, "+1 checked file\n", 17);
		cur_file = cur_file->next;
	}
	if (new_input_fd != -2)
		return (new_input_fd);
	else
		return (old_input_fd);
}

int ft_heredoc_to_fd(char *string)
{
	if (string)
		return (0);
	else
		return (1);
}
