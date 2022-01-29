#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "constants.h"
# include <stdio.h>
# include "readline/readline.h"
# include "readline/history.h"

//enum function {
//	ECHO,
//	CD,
//	PWD,
//	EXPORT,
//	UNSET,
//	ENV,
//	EXIT
//};

typedef struct s_param {
	char			*name;
	char			*value;
	struct s_param	*next;
}	t_param;

typedef struct s_data {
	int 			isMyFunction;
	char			*in_file;
	char			*out_file;
	char			**command;
	t_param			*param;
	struct s_data	*next;
}	t_data;

typedef struct s_general {
	t_param			*env;
	int				err_number;
}	t_common;

/* PROTOTYPE */
//   --- utils/data.c ---   //
char	*get_substr(const char *str, size_t start, size_t end);
//   --- utils/data.c ---   //

//   --- data/param.c ---   //
t_param	*init_param(const char *str);
void	add_param(t_param **begin, t_param *new);
void	delete_param(t_param **begin, t_param *element);
//   --- data/param.c ---   //

//   --- data/common.c ---   //
t_common	*init_common_data(const char **envp);
//   --- data/common.c ---   //

/* PROTOTYPE */

#endif
