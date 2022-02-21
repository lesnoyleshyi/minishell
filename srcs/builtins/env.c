#include "../../includes/minishell.h"

/**
 * This function prints all values stored
 * in the global variable "g_common->env"
 */

void	env(void)
{
	t_param	*param;

	param = g_common->env;
	while (param != NULL)
	{
		printf("%s=%s\n", param->name, param->value);
		param = param->next;
	}
}
