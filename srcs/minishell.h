#ifndef MINISHELL_H
#define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "readline/readline.h"
# include "readline/history.h"
# define EXIT_COMMAND_NOT_FOUND	127
# define ENOEXEC 				8
# define EX_BINARY_FILE			126
# define NO_PIPE				-1

//extern volatile int last_command_exit_value;
int					last_command_exit_value;
char				**export_env;


enum file_type {
	E_IN,
	E_OUT,
	E_APPEND,
	E_HEREDOC
};

//Structure representing an array of file descriptors which we have to close
//as soon as we fork() in command-executing functions;
//Why it's not an array of ints? Because bash do the same ;) Ok, it consumes
//less memory, and we shouldn't think how to terminate array of ints
//because we have "size" field.
//
//You should think of "fd_bitmap" field as array of memory cells, where every
//cell contains single file descriptor
typedef struct s_fd_bitmap {
	int		size;
	char	*fd_bitmap;
}				t_fd_bitmap;

typedef struct s_param {
	char			*name;
	char			*value;
	struct s_param	*next;
}				t_param;

typedef	struct	s_common {
	int				err_number;
	t_param			*env;
	t_param			*local_param;
}				t_common;

typedef	struct	s_file {
	int				mod;
	char			*name;
	struct s_file	*next;
}				t_file;

typedef	struct	s_data {
	int				isMyFunction;
	char			**command;
	t_file			*file;
	struct s_data	*next;
}				t_data;



int		ft_execute_cmd(char *cmd_w_args[]);
void	ft_execute_builtin(char *cmd_w_args[]);
void	ft_echo(char *cmd_w_args[]);
void	ft_cd(const char *path);
void	ft_pwd(void);
void	ft_export(char *cmd_w_args[]);
void	ft_unset(char *cmd_w_args[]);
void	ft_env(void);
void	ft_exit(char *cmd_w_args[]);

int		ft_open_output_file(char *filename, int mode);
int		ft_open_input_file(char *filename);

int		ft_get_child_exit_status(pid_t pid);
void	ft_skip_after_child_failure(int pipe_input, int pipe_output, t_data *cmd_data);

#endif
