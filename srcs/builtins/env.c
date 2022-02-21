#include "../../includes/minishell.h"

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
