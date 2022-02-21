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
# include <readline/readline.h>
# include "readline/history.h"
# define EXIT_COMMAND_NOT_FOUND	127
# define ENOEXEC 				8
# define EX_BINARY_FILE			126
# define NO_PIPE				-1
# define AMBIGUOUS_REDIRECT		-1
# define HEREDOC_REDIRECT		-4		//here-doc temp file can't be created


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

typedef struct s_param {
	int				app;
	char			*name;
	char			*value;
	struct s_param	*next;
}	t_param;

typedef struct s_common {
	int				err_number;
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

t_common	*g_common;

/* PROTOTYPE */
//   --- utils ---   //
void		first_pars(const char *line, t_list **begin);
void		second_parser(t_list **begin, t_data *data);
char		*replace_all_param(char *str);
int			get_mod_file(t_list **begin, t_list **element, int mod);

//   --- string ---   //
int			ft_strcmp(const char *s1, const char *s2);
char		*get_unsubstr(char *str, size_t start, size_t end);
char		*insert_srt(char *str, char *substr, size_t *index);
char		*get_substr(const char *str, size_t start, size_t end);
void		remove_all_quote(char *str);

//   --- checks ---   //
int			check_function(const char *function);
int			check_determinate(char c);
int			check_get_param(const char *str);
int			check_spec_sym(char c);
int			check_content(const char *str, int flag);

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
int			add_new_data(t_data **data);
void		destroy_data(t_data	**data);

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

/* PROTOTYPE */

/* STYCHO */
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

char	*ft_get_abs_path_to_binary(char *pathname);
/* STYCHO */

void		print_param(t_param *param);
void		print_common_param(void);
void		print_list(t_list *list);
void		print_data(t_data *data);
void		print_array_string(char **array);
#endif
