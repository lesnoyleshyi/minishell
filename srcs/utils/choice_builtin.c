#include "../../includes/minishell.h"

void	choice_builtin(t_data *data, int flag)
{
	if (flag == E_NOT_FUNCTION)
		return ;
	else if (flag == E_ENV)
		env();
	else if (flag == E_EXPORT)
		export(&data->command[1]);
	else if (flag == E_ECHO)
		echo(&data->command[1]);
	if (data)
		;
}
