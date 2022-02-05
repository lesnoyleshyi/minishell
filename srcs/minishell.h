#ifndef MINISHELL_H
#define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "readline/readline.h"
# include "readline/history.h"

typedef	struct	simple_command {
	struct s_file			*input;
	struct s_file			*output;
	char					**cmd_w_args;
	struct simple_command	*next;
}				t_s_cmd;

typedef	struct	s_file {
	int				append;
	char			*name;
	struct s_file	*next;
}				t_file;

int		ft_execute_cmd(char *cmd_w_args[]);
void	ft_execute_builtin(char *cmd_w_args[]);
void	ft_echo(char *cmd_w_args[]);
void	ft_cd(const char *path);
void	ft_pwd(void);
void	ft_export(char *cmd_w_args[]);
void	ft_unset(char *cmd_w_args[]);
void	ft_env(void);
void	ft_exit(char *cmd_w_args[]);

int		ft_open_output_file(char *filename);
int		ft_open_input_file(char *filename);

int		ft_get_child_exit_status(pid_t pid);
void	ft_skip_after_child_failure(int pipe_input, int pipe_output, t_s_cmd *cmd_data);

#endif
