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

//Opens file referenced by filename, no matter where this file is located
//and no matter what kind of file it is - regular/heredoc/for input/for output
int	open_file(char *filename, int mode_for_open);

//We'll receive full string that parser expands from heredoc, not pathname.
//This function creates pipe or temporary file that'll contain this string.
//Decision about storage rely on len(heredoc_string) and max size of pipe.
int	heredoc_to_fd(char *heredoc_string);

//Creates pipe and writes heredoc_len bytes from string to this pipe,
//closes pipe_input at the end of writing
//*
//No error handling here, but it should be
int	heredoc_to_pipe(char *string, int heredoc_len);

//Creates temp file and writes heredoc_len bytes to it
//*
//IDK how to delete this file without using global variable
int	heredoc_to_temp_file(char *string, int heredoc_len);

//Changes input_source from previous (could be stdin or pipe's output) to output
//file/heredoc if there is any in redirect_list
//*
//Closes previous input fd only if
// it finds any input redirection in redirect_list
//*
//Returns -1 in case of error
//Opens input files(< or <<stop_word) in cycle if there are some.
//Leaves only the last opened, close other ones.
//
int	choose_inp_src(t_file *redirect_list);

int	choose_inp_src(t_file *redirect_list)
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
			input_fd = open_file(cur_file->name, cur_file->mod);
			if (input_fd == -1)
				break ;
		}
		cur_file = cur_file->next;
	}
	if (input_fd == -1)
	{
		if (cur_file->mod == E_HEREDOC)
			return (perror_and_return("heredoc", 1));
		return (perror_and_return(cur_file->name, HEREDOC_REDIRECT));
	}
	safe_substitute_fd(input_fd, 0);
	return (0);
}

int	open_file(char *filename, int mode_for_open)
{
	int		fd;

	if (mode_for_open == E_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 00644);
	else if (mode_for_open == E_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	else if (mode_for_open == E_IN)
		fd = open(filename, O_RDONLY);
	else if (mode_for_open == E_HEREDOC)
		fd = heredoc_to_fd(filename);
	else
		return (-1);
	return (fd);
}

int	heredoc_to_fd(char *string)
{
	int	fd;
	int	heredoc_len;

	if (string == NULL)
		heredoc_len = 0;
	else
		heredoc_len = ft_strlen(string);
	if (heredoc_len == 0)
		fd = open_file("/dev/null", O_RDONLY);
	else if (heredoc_len < PIPE_BUF)
		fd = heredoc_to_pipe(string, heredoc_len);
	else
		fd = heredoc_to_temp_file(string, heredoc_len);
	return (fd);
}

int	heredoc_to_pipe(char *string, int heredoc_len)
{
	int		pipe_fds[2];

	pipe(pipe_fds);
	write(pipe_fds[1], string, heredoc_len);
	close(pipe_fds[1]);
	return (pipe_fds[0]);
}

int	heredoc_to_temp_file(char *string, int heredoc_len)
{
	int	fd;

	unlink(".yaiyurassalinazelenysapog");
	fd = open(".yaiyurassalinazelenysapog", O_RDWR | O_CREAT | O_TRUNC, 00600);
	write(fd, string, heredoc_len);
	return (fd);
}
