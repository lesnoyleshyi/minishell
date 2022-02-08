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

void	ft_apply_redirections_in(int pipe_input, int pipe_output, t_file *input);
void	ft_apply_redirections_out(int pipe_input, int pipe_output, t_file *output, t_data *cmd_data);

void	ft_apply_redirections(t_file *io_list, int reserved_io[2]);

int	ft_apply_heredocs(t_file *io_list, int reserved_stdin);
int	ft_get_heredoc(int reserved_stdin, char *stop_word);
int	ft_get_inp_srcs_count(t_file *io_list);

void	ft_apply_file_redirections(t_file *io_list);
void	ft_close_file_and_reset_stdio(int *fd);

void	ft_execute_pipeline(t_data *command_list)
{
	int		pipe_fds[2];
	pid_t	pid;
	t_data	*cmd_data;
	int		reserved_stdin_stdout[2];
	char	buf;

	reserved_stdin_stdout[0] = dup(0);
	reserved_stdin_stdout[1] = dup(1);
	cmd_data = command_list;
	while (cmd_data != NULL)
	{
		ft_apply_redirections(cmd_data->file, reserved_stdin_stdout);
		pipe(pipe_fds);
		pid = fork();
		if (pid == 0)
		{
//			ft_apply_redirections_in(pipe_fds[1], pipe_fds[0], cmd_data->input);
			close(pipe_fds[0]);
			dup2(pipe_fds[1], 1);
			close(pipe_fds[1]);
			ft_execute_cmd(cmd_data->command);
		}
		else
		{
			if (ft_get_child_exit_status(pid) == 0)
			{
				close(pipe_fds[1]);
				if (cmd_data->next == NULL)
				{
					while (read(0, &buf, 1) == 1)
						write(1, &buf, 1);
					close(1);
				}
				else
				{
					close(pipe_fds[1]);
				}
//				ft_apply_redirections_out(pipe_fds[1], pipe_fds[0], cmd_data->output, cmd_data);
			}
			else
				ft_skip_after_child_failure(pipe_fds[1], pipe_fds[0], cmd_data);
			cmd_data = cmd_data->next;
		}
	}
	dup2(reserved_stdin_stdout[0], 0);
}

void	ft_apply_redirections(t_file *io_list, int reserved_io[2])
{
	int	stdin_fd;
	int stdout_fd;

	stdin_fd = ft_apply_heredocs(io_list, reserved_io[0]);
	dup2(stdin_fd, 0);
	if (stdin_fd != 0)
		close(stdin_fd);
//	после этой строки stdin-у соответствует fd=0, но он может указывать
//	как на выход из пайпа, так и на ввод с клавиатуры
	ft_apply_file_redirections(io_list);
//	после этой строки stdin будет 0, но может указывать как на 1)выход из пайпа,
//	так на 2)ввод с клавиатуры а еще 3) на файл
}

int	ft_apply_heredocs(t_file *io_list, int reserved_stdin)
{
	t_file	*inp_src;
	int		heredoc_fd;
	int		inp_src_pos;

	inp_src = io_list;
	inp_src_pos = 0;
	heredoc_fd = 0;
	while (inp_src != NULL)
	{
		if (inp_src->mod != E_HEREDOC)
		{
			inp_src_pos += (inp_src->mod == E_IN);
			inp_src = inp_src->next;
			continue;
		}
		heredoc_fd = ft_get_heredoc(reserved_stdin, inp_src->name);
		if (++inp_src_pos < ft_get_inp_srcs_count(io_list))
		{
			close(heredoc_fd);
			heredoc_fd = 0;
		}
		inp_src = inp_src->next;
	}
	return (heredoc_fd);
}

int	ft_get_heredoc(int reserved_stdin, char *stop_word)
{
	int		pipe_fds[2];
	pid_t	pid;
	char	*user_input;

	dup2(reserved_stdin, 0);
	pipe(pipe_fds);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fds[0]);
		dup2(pipe_fds[1], 1);
		close(pipe_fds[1]);
//		rl_replace_line(">", 0);
//		rl_redisplay();
		while (1)
		{
			user_input = readline(">");
			if (ft_strncmp(user_input, stop_word, 100) == 0)
			{
				free(user_input);
				exit(0);
			}
			else
			{
				write(1, user_input, ft_strlen(user_input));
				free(user_input);
			}
		}
	}
	else
	{
		close(pipe_fds[1]);
	}
	return (pipe_fds[0]);
}

int	ft_get_inp_srcs_count(t_file *io_list)
{
	t_file	*inp_src;
	int		inp_srcs_count;

	inp_srcs_count = 0;
	inp_src = io_list;
	while (inp_src != NULL)
	{
		if (inp_src->mod == E_IN || inp_src->mod == E_HEREDOC)
			inp_srcs_count += 1;
		inp_src = inp_src->next;
	}
	return (inp_srcs_count);
}

void	ft_apply_file_redirections(t_file *io_list)
{
	t_file	*io_src;
	int		inp_src_pos;
	int		stdin_fd;
	int		stdout_fd;

	io_src = io_list;
	stdin_fd = 0;
	stdout_fd = 1;
	while (io_src != NULL)
	{
		if (io_src->mod == E_IN)
		{
			inp_src_pos += 1;
			stdin_fd = ft_open_input_file(io_src->name);
			if (inp_src_pos < ft_get_inp_srcs_count(io_list))
				ft_close_file_and_reset_stdio(&stdin_fd);
		}
		if (io_src->mod == E_HEREDOC)
			inp_src_pos += 1;
		if (io_src->mod == E_OUT || io_src->mod == E_APPEND)
		{
			if (stdout_fd != 1)
			{
				close(stdout_fd);
				stdout_fd = 1;
			}
			stdout_fd = ft_open_output_file(io_src->name, io_src->mod);
		}
		io_src = io_src->next;
	}
	if (stdin_fd != 0)
	{
		dup2(stdin_fd, 0);
		close(stdin_fd);
	}
	if (stdout_fd != 1)
	{
		dup2(stdout_fd, 0);
		close(stdout_fd);
	}
}

void	ft_close_file_and_reset_stdio(int *fd)
{
	close(*fd);
	*fd = 0;
}

int	ft_execute_cmd(char *cmd_w_args[])
{
	int	fail_ex_status;

	if (ft_strchr(cmd_w_args[0], '/') == NULL)
	{
		printf("it is builtin!\n");
		ft_execute_builtin(cmd_w_args);
		exit(2);
	}
	else
		fail_ex_status = execve(cmd_w_args[0], cmd_w_args, cmd_w_args);
	//	ft_clear_env(env);
	exit(fail_ex_status);
}

void	ft_apply_redirections_in(int pipe_input, int pipe_output, t_file *input)
{
	t_file	*inp_file;
	int		inp_fd;

	close(pipe_output);
	inp_fd = 0;
	inp_file = input;
	while (inp_file != NULL)
	{
		inp_fd = ft_open_input_file(inp_file->name);
		if (inp_fd == -1)
			exit(1);
		inp_file = inp_file->next;
	}
	dup2(inp_fd, 0);
	if (inp_fd != 0)
		close(inp_fd);
	dup2(pipe_input, 1);
	close(pipe_input);
}

void	ft_apply_redirections_out(int pipe_input, int pipe_output, t_file *output, t_data *cmd_data)
{
	t_file	*out_file;
	int		out_fd;
	char	buf;

	close(pipe_input);
	out_fd = 1;
	out_file = output;
	while (out_file != NULL)
	{
		out_fd = ft_open_output_file(out_file->name, out_file->mod);
		if (out_file->next != NULL)
			close(out_fd);
		out_file = out_file->next;
	}
	if (cmd_data->next == NULL || output != NULL)
	{
		while (read(pipe_output, &buf, 1) == 1)
			write(out_fd, &buf, 1);
		if (out_fd != 1)
			close(out_fd);
	}
	else
		dup2(pipe_output, 0);
	close(pipe_output);
}

int	ft_open_input_file(char *filename)
{
	int		input_file_fd;
	char	*cur_dir;
	char	*cur_dir_w_slash;
	char	*full_path;

	if (filename == NULL)
		return (1);
	if (ft_strchr(filename, '/') != NULL)
		input_file_fd = open(filename, O_RDONLY);
	if (ft_strchr(filename, '/') == NULL)
	{
		cur_dir = getcwd(NULL, 0);
		cur_dir_w_slash = ft_strjoin(cur_dir, "/");
		full_path = ft_strjoin(cur_dir_w_slash, filename);
		input_file_fd = open(full_path, O_RDONLY);
		if (input_file_fd == -1)
		{
			write(2, "minishell: ", 11);
			perror(filename);
		}
		free(full_path);
		free(cur_dir_w_slash);
		free(cur_dir);
	}
	return (input_file_fd);
}

int	ft_open_output_file(char *filename, int mode)
{
	int		output_file_fd;
	char	*cur_dir;
	char	*cur_dir_w_slash;
	char	*full_path;

	if (filename == NULL)
		return (1);
	if (ft_strchr(filename, '/') != NULL)
		output_file_fd = open(filename, O_WRONLY | O_CREAT
		| O_TRUNC * (mode == E_OUT) | O_APPEND * (mode == E_APPEND), 00644);
	if (ft_strchr(filename, '/') == NULL)
	{
		cur_dir = getcwd(NULL, 0);
		cur_dir_w_slash = ft_strjoin(cur_dir, "/");
		full_path = ft_strjoin(cur_dir_w_slash, filename);
		output_file_fd = open(full_path, O_WRONLY | O_CREAT
		| O_TRUNC * (mode == E_OUT) | O_APPEND * (mode == E_APPEND), 00644);
		free(full_path);
		free(cur_dir_w_slash);
		free(cur_dir);
	}
	return (output_file_fd);
}

int	ft_get_child_exit_status(pid_t pid)
{
	int exit_status;

	waitpid(pid, &exit_status, 0);
	if (WEXITSTATUS(exit_status) == 0)
		return (0);
	else
		return (WEXITSTATUS(exit_status));
//		here we (theoretically) can catch different ex_st in case of signal termination
}

void	ft_skip_after_child_failure(int pipe_input, int pipe_output, t_data *cmd_data)
{
	close(pipe_input);
	if (cmd_data->next != NULL)
		dup2(pipe_output, 0);
	close(pipe_output);
}