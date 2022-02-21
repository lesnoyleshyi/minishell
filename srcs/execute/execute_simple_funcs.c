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

#include "../../includes/minishell.h"

void	ft_apply_redirections_in(int pipe_input, int pipe_output, char *infile);
void	ft_apply_redirections_out(int pipe_input, int pipe_output, char *outfile, t_s_cmd *cmd_data);
int		ft_get_child_error(int child_exit_status);

void	ft_execute_pipeline(t_s_cmd *command_list)
{
	int		pipe_fds[2];
	pid_t	pid;
	t_s_cmd	*cmd_data;
	int		exit_status;
	int		reserved_stdin;

	cmd_data = command_list;
	reserved_stdin = dup(0);
	while (cmd_data != NULL)
	{
		pipe(pipe_fds);
		pid = fork();
		if (pid == 0)
		{
			ft_apply_redirections_in(pipe_fds[1], pipe_fds[0], cmd_data->input);
			ft_get_child_error(ft_execute_cmd(cmd_data->cmd_w_args));
		}
		else
		{
			waitpid(pid, &exit_status, 0);
			ft_apply_redirections_out(pipe_fds[1], pipe_fds[0], cmd_data->output, cmd_data);
			cmd_data = cmd_data->next;
		}
	}
	dup2(reserved_stdin, 0);
}

int	ft_execute_cmd(char *cmd_w_args[])
{
	int	fail_ex_status;

	if (ft_strchr(cmd_w_args[0], '/') == NULL)
	{
		printf("it is builtin!\n");
		ft_execute_builtin(cmd_w_args);
		return (228);
	}
	else
	{
		fail_ex_status = execlp(cmd_w_args[0], "kek", cmd_w_args[1], NULL);
//		fail_ex_status = execve(cmd_w_args[0], cmd_w_args, env);
	}
//	ft_clear_env(env);
	return (fail_ex_status);
}

void	ft_apply_redirections_in(int pipe_input, int pipe_output, char *infile)
{
	int		inp_fd;

	close(pipe_output);
	inp_fd = 0;
	if (infile != NULL)
		inp_fd = open_input_file(infile);
	dup2(inp_fd, 0);
	if (inp_fd != 0)
		close(inp_fd);
	dup2(pipe_input, 1);
	close(pipe_input);
}

void	ft_apply_redirections_out(int pipe_input, int pipe_output, char *outfile, t_s_cmd *cmd_data)
{
	int		out_fd;
	char	buf;

	close(pipe_input);
	out_fd = 1;
	if (outfile != NULL)
		out_fd = open_output_file(outfile);
	if (cmd_data->next == NULL || outfile != NULL)
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

int	open_output_file(char *filename)
{
	int		output_file_fd;
	char	*cur_dir;
	char	*cur_dir_w_slash;
	char	*full_path;

	if (filename == NULL)
		return (1);
	if (ft_strchr(filename, '/') != NULL)
		output_file_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 00644);
	if (ft_strchr(filename, '/') == NULL)
	{
		cur_dir = getcwd(NULL, 1);
		cur_dir_w_slash = ft_strjoin(cur_dir, "/");
		full_path = ft_strjoin(cur_dir_w_slash, filename);
		output_file_fd = open(full_path, O_WRONLY | O_CREAT | O_APPEND, 00644);
		free(full_path);
		free(cur_dir_w_slash);
		free(cur_dir);
	}
	return (output_file_fd);
}

int	open_input_file(char *filename)
{
	int		input_file_fd;
	char	*cur_dir;
	char	*cur_dir_w_slash;
	char	*full_path;

	if (filename == NULL)
		return (1);
	if (ft_strchr(filename, '/') != NULL)
		input_file_fd = open(filename, O_CREAT | O_TRUNC, 00644);
	if (ft_strchr(filename, '/') == NULL)
	{
		cur_dir = getcwd(NULL, 1);
		cur_dir_w_slash = ft_strjoin(cur_dir, "/");
		full_path = ft_strjoin(cur_dir_w_slash, filename);
		input_file_fd = open(full_path, O_CREAT | O_TRUNC, 00644);
		free(full_path);
		free(cur_dir_w_slash);
		free(cur_dir);
	}
	return (input_file_fd);
}

int	ft_get_child_error(int child_exit_status)
{
	printf("Exec failed with ex_st %d\n", child_exit_status);
	exit(0);
}