/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 00:13:58 by drayl             #+#    #+#             */
/*   Updated: 2022/02/20 00:14:00 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "constants.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include "readline/history.h"
# include "signal.h"
# define EXIT_COMMAND_NOT_FOUND		127
# define EXIT_COMMAND_IS_DIRECTORY	126
# define ENOEXEC 					8
# define EX_BINARY_FILE				126
# define NO_PIPE					-1
# define AMBIGUOUS_REDIRECT			-1
# define HEREDOC_REDIRECT			-4	//here-doc temp file can't be created
# define PIPE_BUF					4096

enum e_function {
	E_NOT_FUNCTION,
	E_ECHO,
	E_CD,
	E_PWD,
	E_EXPORT,
	E_UNSET,
	E_ENV,
	E_EXIT
};

enum e_special_symbols {
	E_NOT_SPEC_SYM,
	E_REDIR_IN,
	E_REDIR_OUT,
	E_INIT_PARAM,
	E_PIPE
};

enum e_file_type {
	E_IN,
	E_OUT,
	E_HEREDOC,
	E_APPEND
};

enum e_errors {
	OK,
	KO,
	SYNTAX_ERROR,
	MEMORY_ERROR,
};

enum e_param_type {
	NEW_PARAM,
	ENV_PARAM,
	LOCAL_PARAM
};

enum e_err_msg_code {
	CMD_NOT_FOUND,
	CMD_IS_DIR
};

enum e_pipe_relation {
	WITHIN_PIPELINE,
	NOT_IN_PIPELINE
};

typedef struct s_param {
	char			*name;
	char			*value;
	struct s_param	*next;
}	t_param;

typedef struct s_common {
	int				err_number;
	char			*home;
	char			*pwd;
	char			*history_file;
	t_list			*history;
	t_param			*env;
	t_param			*local_param;
	t_param			*new_list;
}	t_common;

typedef struct s_file {
	int				mod;
	char			*name;
	struct s_file	*next;
}	t_file;

typedef struct s_data {
	char			**command;
	t_file			*file;
	t_param			*param_list;
	struct s_data	*next;
}	t_data;

typedef struct s_pipeline_fds {
	int	fd_in;
	int	fd_out;
	int	pipe_fds[2];
	int	reserved_stdin;
	int	reserved_stdout;
}				t_pipeline_fds;

t_common	*g_common;

/* PROTOTYPE */

//   --- utils ---   //
void		first_pars(const char *line, t_list **begin);
int			second_parser(t_list **begin, t_data *data);
char		*replace_all_param(char *str);
int			get_mod_file(t_list **begin, t_list **element, int mod);
int			read_heredoc(t_data *data);
void		execute_builtin(t_data *data, int flag, int pipe_flag);
void		read_old_history(void);
void		add_new_history(void);
void		add_param_without_export(t_param **begin);

//   --- string ---   //
int			ft_strcmp(const char *s1, const char *s2);
char		*get_unsubstr(char *str, size_t start, size_t end);
char		*insert_srt(char *str, char *substr, size_t *index);
char		*get_substr(const char *str, size_t start, size_t end);
char		*get_substr_for_value(const char *str, size_t start, size_t end);
void		remove_all_quote(char *str);
char		*remove_string(char *str);

//   --- checks ---   //
int			is_builtin(const char *function);
int			check_determinate(char c);
int			check_get_param(const char *str);
int			check_spec_sym(char c);
int			check_content(const char *str, int flag);
int			check_presence_param(t_param **element, char *name);
int			check_common(void);
char		check_param_name(char *str);
int			check_valid_param_name(char **arg);
int			check_param_name_for_unset(char **arg);

//   --- data/param.c ---   //
t_param		*init_param(const char *str);
void		add_param(t_param **begin, t_param *new);
void		delete_param(t_param **begin, t_param *element);
void		destroy_param(t_param **begin);
char		*get_param_value(const char *name);

//   --- data/common.c ---   //
t_common	*init_common_data(char **envp);
t_common	*destroy_common_date(void);

//   --- data/data.c ---   //
t_data		*create_data(void);
t_data		*init_data(const char *line);
void		destroy_data(t_data	**data);
int			add_new_data(t_data **data);

//   --- data/string_array.c ---   //
char		**convert_list_to_array(t_list *lst);
char		**convert_sublist_to_array(t_list *begin, t_list *stop);
char		**destroy_array(char **mas);

//   --- data/file.c ---   //
t_file		*init_new_file(char *name);
void		add_new_file(t_file **begin, t_file *new);
void		destroy_file(t_file **file);

//   --- data_list.c ---   //
t_list		*remove_element(t_list **begin, t_list *element);
void		remove_all_list(t_list **begin);
void		remove_first_element(t_list **begin);

//   --- builtins ---   //
void		env(void);
void		export(char **arg);
void		echo(char **arg);
void		unset(char **arg);
void		cd(char *dir);
void		pwd(void);
void		b_exit(int exit_status, int pipe_flag);

//   --- error/put_error.c ---   //
int			syntax_error(char *substr);
void		memory_error(void);
void		put_error_param_name(char ch);
void		put_error_id_for_unset(char *arg);
void		put_error_cd(char *dir_name, char *message, int oldpwd_flag);

/* PROTOTYPE */

/* STYCHO */
//   			--- /srcs/execute/execute_builtin.c ---   					//
void		execute_pipeline(t_data *command_list);

//   			--- /srcs/execute/execute_simple.c ---   					//
void		execute(t_data *data);
void		execute_simple(t_data *cmd_data);
void		execute_binary(t_data *cmd_data);
void		execute_null_command(t_file *redir_list);
void		ft_execve(char *pathname, char *argv[], char *envp[]);

//   			--- /srcs/execute/choose_output.c ---   					//
void		execute_pipeline(t_data *command_list);
void		execute_in_child(t_pipeline_fds *pipe_fds_struct, t_data *cmd);
void		initialise_stdin_stdout(t_pipeline_fds *pipe_fds_struct);
void		reset_stdin_stdout(t_pipeline_fds *pipe_fds_struct);
void		ft_wait(pid_t last_pid);

//   			--- /srcs/redirect/choose_input.c ---  						 //
int			choose_inp_src(t_file *redirect_list);
int			open_file(char *filename, int mode_for_open);
int			heredoc_to_fd(char *heredoc_string);
int			heredoc_to_pipe(char *string, int heredoc_len);
int			heredoc_to_temp_file(char *string, int heredoc_len);

//   			--- /srcs/redirect/choose_output.c ---   					//
int			choose_output(int *old_output, t_file *redir_list);
int			is_here_output_redirections(t_file *list_of_all_redirections);
int			check_read_perm(char *filename);
int			do_last_cmd_redirs(t_pipeline_fds *fds_s, t_file *redir_list,
				pid_t *pid);

//   			--- /srcs/redirect/redirect_utils.c ---   					//
int			do_piping(t_pipeline_fds *pipe_fds_struct, char *cmd_name);
int			safe_substitute_fd(int old_fd, int new_fd);
int			substitute_fd(int old_fd, int new_fd);

//   --- /srcs/utils/new_env.c ---   //
char		**new_env(t_param *begin);
char		**param_list_to_arr(t_param *param_list);
char		*param_to_string(t_param *param);
size_t		param_list_len(t_param *param);
size_t		char_p_arr_len(char **arr);

//   					--- signal/common_signals.c ---   					//
void		rl_replace_line(const char *text, int clear_undo);
void		init_signal_handling(void (*handler)(int));

//   					--- signal/child_signals.c ---   					//
void		child_handler(int signal);
void		child_quit(void);
void		clear_child_input(void);

//   					--- signal/parent_signals.c ---   					//
void		main_handler(int signal);
void		do_nothing(void);
void		clear_input(void);

//   --- error/error.c ---   //
void		custom_message_exit(char *pathname, int message_code,
				int exit_status);
int			perror_and_return(char *message, int ret_val);
int			translate_errno_to_exit_status(int errno_val);
int			get_child_exit_status(pid_t pid);
int			cmd_not_found(char *str);

//   --- execute/get_abs_path.c ---   //
char		*get_abs_path_to_binary(char *pathname);
int			is_directory(char *pathname);
void		free_arr(char **paths_arr);
/* STYCHO */

void		print_param(t_param *param);
void		print_common_param(void);
void		print_list(t_list *list);
void		print_data(t_data *data);
void		print_array_string(char **array);
#endif
