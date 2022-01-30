#ifndef MINISHELL_H
#define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include "readline/readline.h"
# include "readline/history.h"

typedef	struct	simple_command {
	char					*input;
	char					*output;
	char					**cmd_w_args;
	struct simple_command	*next;
//	struct simple_command	*prev;
}				t_s_cmd;

#endif
