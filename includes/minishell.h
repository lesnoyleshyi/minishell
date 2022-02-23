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
# include <readline/readline.h>
# include "readline/history.h"
# define EXIT_COMMAND_NOT_FOUND	127
# define ENOEXEC 				8
# define EX_BINARY_FILE			126
# define NO_PIPE				-1
# define AMBIGUOUS_REDIRECT		-1
# define HEREDOC_REDIRECT		-4		//here-doc temp file can't be created
# define PIPE_BUF				4096

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
	E_GET_PARAM,
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

typedef struct s_param {
	int				app;
	char			*name;
	char			*value;
	struct s_param	*next;
}	t_param;

typedef struct s_common {
	int				err_number;
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
	int fd_out;
	int pipe_fds[2];
	int reserved_stdin;
	int reserved_stdout;
}				t_pipeline_fds;

t_common	*g_common;

/* PROTOTYPE */

//   --- utils ---   //
void		first_pars(const char *line, t_list **begin);
void		second_parser(t_list **begin, t_data *data);
char		*replace_all_param(char *str);
int			get_mod_file(t_list **begin, t_list **element, int mod);
int			read_heredoc(t_data *data);
void		choice_builtin(t_data *data, int flag);
void		read_old_history(void);
void		add_new_history(void);

//   --- string ---   //
int			ft_strcmp(const char *s1, const char *s2);
char		*get_unsubstr(char *str, size_t start, size_t end);
char		*insert_srt(char *str, char *substr, size_t *index);
char		*get_substr(const char *str, size_t start, size_t end);
char		*get_substr_for_value(const char *str, size_t start, size_t end);
void		remove_all_quote(char *str);
char		*remove_string(char *str);

//   --- checks ---   //
int			check_function(const char *function);
int			check_determinate(char c);
int			check_get_param(const char *str);
int			check_spec_sym(char c);
int			check_content(const char *str, int flag);
int			check_presence_param(t_param **element, char *name);
int			check_valid_param_name(char **arg);
char		check_param_name(char *str);

//   --- data/param.c ---   //
t_param		*init_param(const char *str);
void		add_param(t_param **begin, t_param *new);
void		delete_param(t_param **begin, t_param *element);
void		destroy_param(t_param **begin);
char		*get_param_value(const char *name);

//   --- data/common.c ---   //
t_common	*init_common_data(const char **envp);
void		destroy_common_date(void);

//   --- data/data.c ---   //
t_data		*create_data(void);
t_data		*init_data(const char *line);
void		destroy_data(t_data	**data);
int			add_new_data(t_data **data);

//   --- data/string_array.c ---   //
char		**convert_list_to_array(t_list *lst);
char		**convert_sublist_to_array(t_list *begin, t_list *stop);
void		destroy_array(char **mas);

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

/* PROTOTYPE */

/* STYCHO */
//   --- execute/execute_funcs.c ---   //
int	ft_execute_pipeline(t_data *command_list, char *envp[]);
int	ft_get_child_exit_status(pid_t pid);

//   --- execute/choose_output.c ---   //
int	ft_open_file(char *filename, int mode_for_open);
int	ft_choose_output(int *old_output, t_file *redir_list);
int ft_do_piping(t_pipeline_fds *pipe_fds_struct, char *cmd_name);
int ft_is_here_output_redirections(t_file *list_of_all_redirections);
int	ft_make_last_cmd_redirs(t_pipeline_fds *pipeline_fds_s, t_file *redir_list);

//   --- execute/choose_input.c ---   //
int	ft_choose_inp_src(t_file *redirect_list);

//   --- signal/signal_funcs.c ---   //
void	ft_clear_input(int signal);

//   --- error/error.c ---   //
int		ft_perror_and_return(char *message, int ret_val);
void	ft_exit_command_not_found(char *filename);
/* STYCHO */

void		print_param(t_param *param);
void		print_common_param(void);
void		print_list(t_list *list);
void		print_data(t_data *data);
void		print_array_string(char **array);
#endif

