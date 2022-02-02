#ifndef MINISHELL_H
#define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include "readline/readline.h"
# include "readline/history.h"

typedef	struct	simple_command {
	char					*input;
	char					*output;
	char					**cmd_w_args;
	struct simple_command	*next;
//	struct simple_command	*prev;
}				t_s_cmd;

void	ft_execute_cmd(char *cmd_w_args[]);
void	ft_execute_builtin(char *cmd_w_args[]);
void	ft_echo(char *cmd_w_args[]);
void	ft_cd(const char *path);
void	ft_pwd(void);
void	ft_export(char *cmd_w_args[]);
void	ft_unset(char *cmd_w_args[]);
void	ft_env(void);
void	ft_exit(char *cmd_w_args[]);

#endif
