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

#include "minishell.h"
//Opens file referenced by filename, no matter where this file is located
int	ft_open_output_file(char *filename, int mode_for_open);

//Returns file descriptor of opened file if there is any of them in file_list
//Returns -2 if file_list is empty or doesn't contain any output files (> or >>)
//Returns -1 in case open() returns -1. It's an error indicator.
int	ft_open_output_files(t_file *file_list)
{
	int		cur_fd;
	t_file	*cur_file;

	cur_fd = -2;
	cur_file = file_list;
	while (cur_file != NULL)
	{
		if (cur_file->mod == E_OUT || cur_file->mod == E_APPEND)
		{
			if (cur_fd != -2)
				close(cur_fd);
			cur_fd = ft_open_output_file(cur_file->name, cur_file->mod);
			if (cur_fd == -1)
				return (-1);
		}
		cur_file = cur_file->next;
	}
	return (cur_fd);
}

int	ft_open_output_file(char *filename, int mode_for_open)
{
	int		output_file_fd;
//	int		oflag;
//	char	*oflag_str;

	if (mode_for_open == E_APPEND)
	{
//		oflag = O_WRONLY | O_CREAT | O_APPEND;
		output_file_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 00644);
	}
	else if (mode_for_open == E_OUT)
	{
//		oflag = O_WRONLY | O_CREAT | O_TRUNC;
		output_file_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	}
	else
	{
//		oflag = 0;
		return (-1);
	}
//	oflag_str = ft_itoa(oflag);
//	write(2, &oflag_str, ft_strlen(oflag_str) + 1);
//	output_file_fd = open(filename, oflag, 00644);
	return (output_file_fd);
}
