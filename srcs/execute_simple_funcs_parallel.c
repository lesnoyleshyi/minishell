#include "minishell.h"

//Closes pipe_in and pipe_out.
//
//pipe_in == NO_PIPE means we'll read from stdin,
//no input redirections were found during parsing;
//
//pipe_out == NO_PIPE means we'll write to stdout,
//no output redirections were found during parsing
void	ft_close_pipes(int pipe_in, int pipe_out);

//Apply	dup2(pipe_in, 0) and dup2(pipe_out, 1)
//
//if pipe_in == NO_PIPE && pipe_out == NO_PIPE, does nothing
//
//pipe_in == NO_PIPE means we'll read from stdin,
//no input redirections were found during parsing
//
//pipe_out == NO_PIPE means we'll write to stdout,
//no output redirections were found during parsing
void	ft_do_piping(int pipe_in, int pipe_out);

//Just closes every file descriptor in fds_bitmap.
//"fd_bitmap" field of "t_fd_bitmap" struct is not a string,
//it's an array of cells in memory where every cell contains one file descriptor
void	ft_close_fds(t_fd_bitmap *fds_bitmap);

//Executes standard execve() inside itself.
//Tries executing cmd_name as shell script in case execve() returns
//or does just some error handling to return correct exit status
int	ft_shell_execve(char *cmd_name, char *argv[], char *env[]);

void	execute_pipeline(t_data *cmd_data_list)
{
	t_data	*cmd_data;

	cmd_data = cmd_data_list;
	while (cmd_data != NULL)
	{

		cmd_data = cmd_data->next;
	}
}

int	execute_simple(t_data *cmd_data, int pipe_in, int pipe_out, t_file *fds_to_close)
{
	int 	already_forked;
	int		do_fork;
	int		ex_status;
	pid_t	pid;
	char	*words;

	already_forked = 0;
	do_fork = pipe_in != -1 || pipe_out != -1;
	if (do_fork)
	{
		ft_maybe_make_export_env();
		pid = fork();
		if (pid == 0)
		{
			already_forked = 1;
			if (fds_to_close)
				ft_close_fds(fds_to_close);
			ft_do_piping(pipe_in, pipe_out);
			pipe_in = -1;
			pipe_out = -1;
		}
		else
		{
			/* Don't let simple commands that aren't the last command in a
	     	pipeline change $? for the rest of the pipeline (or at all). */
			if (pipe_out != -1)
				ex_status = last_command_exit_value;
			ft_close_pipes(pipe_in, pipe_out);
			return (result);
		}
	}
	words = copy_word_list(cmd_data);
	if (words == 0)
	{
		ex_status= ft_execute_null_command(cmd_data->file, pipe_in, pipe_out);
		if (already_forked == 1)
			exit(ex_status);
		return (ex_status);
	}
	if (builtin)
	{
		if (already_forked == 1)
		{
			subshell_level++;
			execute_subshell_builtin_or_function(words, simple_command->redirects, builtin, func,
					 pipe_in, pipe_out, async, fds_to_close, cmdflags);
			subshell_level--;
		}
		else
		{
			ex_status = execute_builtin_or_function(words, builtin, func, simple_command->redirects, fds_to_close,
					 cmdflags);
			return (ex_status);
		}
	}
	ex_status = ft_execute_binary (words, simple_command->redirects, command_line, pipe_in, pipe_out, async, fds_to_close,
								   cmdflags);
	return (ex_status);
}

int	ft_execute_binary(t_data *words, t_file *redirects, int pipe_in, int pipe_out, t_file *fds_to_close)
{
	char	*pathname;
	char	*cmd_name;
	int		ex_status;
	pid_t	pid;

	pathname = words->command[0];
	cmd_name = ft_get_abs_path_to_cmd(pathname);
	ex_status = 0;

	if (cmd_name != NULL)
		ft_maybe_make_export_env();
	if (pipe_in == -1 && pipe_out == -1)
		pid = 0;
	else
		pid = fork();
	if (pid == 0)
	{
		if (fds_to_close)
			ft_close_fds(fds_to_close);
		ft_do_piping(pipe_in, pipe_out);
		if (redirects && ft_do_redirections(redirects) != 0)
			exit(EXIT_FAILURE);
		if (cmd_name == 0)
			exit(EXIT_COMMAND_NOT_FOUND);
		ex_status = ft_shell_execve(cmd_name, words->command, export_env);
	}
	else
	{
		ft_close_pipes(pipe_in, pipe_out);
		return (ex_status);
	}
}

int	ft_shell_execve(char *cmd_name, char *argv[], char *env[])
{
	int err;
	char buf[128];
	int fd;
	int sample_len;

	execve(cmd_name, argv, env);
	err = errno;
	if (err != ENOEXEC)
	{
		if (ft_cmd_is_dir(cmd_name))
			ft_report_err("%s is a directory", cmd_name);
		else
		{
			errno = err;
			ft_report_err("%s:%s", cmd_name, strerror(errno));
		}
		return (last_command_exit_value);
	}
	fd = open(cmd_name, O_RDONLY);
	if (fd >= 0)
	{
		sample_len = read(fd, &buf, 128);
		close(fd);
	}
	else
		sample_len = -1;
	if (sample_len == 0)
		return (EXIT_SUCCESS);
	if (sample_len > 0)
	{
		if (sample_len > 0 && buf[0] == '#' && buf[1] == '!')
			return (ft_execute_script(buf, sample_len, cmd_name, args, env));
		else
		{
			if (ft_check_first_line_in_script(buf, sample_len) != 0)
			{
				ft_report_error(("%s: cannot execute binary file: %s"), cmd_name, strerror (err));
				errno = err;
				return (EX_BINARY_FILE);
			}
		}
	}
	else
		ft_report_error("Can't open file"); //в оригинале дальше какая-то дичь
}

void	ft_close_pipes(int pipe_in, int pipe_out)
{
	if (pipe_in >= 0)
		close(pipe_in);
	if (pipe_out >= 0)
		close(pipe_out);
}

void	ft_do_piping(int pipe_in, int pipe_out)
{
	if (pipe_in != NO_PIPE)
	{
		if (dup2(pipe_in, 0) < 0)
			ft_report_error("cannot duplicate fd %d to fd %d", pipe_in, 0);
		if (pipe_in > 0)
			close(pipe_in);
	}
	if (pipe_out != NO_PIPE)
	{
		if (dup2(pipe_out, 1) < 0)
			ft_report_error("cannot duplicate fd %d to fd %d", pipe_out, 1);
		if (pipe_out == 0 || pipe_out > 1)
			close(pipe_out);
	}
}

void	ft_close_fds(t_fd_bitmap *fds_bitmap)
{
	int	i;

	if (fds_bitmap == NULL)
		return;
	i = 0;
	while (i < fds_bitmap->size)
	{
		if (fds_bitmap->fd_bitmap[i] != 0)
		{
			close(fds_bitmap->fd_bitmap[i]);
			fds_bitmap->fd_bitmap[i] = 0;
		}
	}
}