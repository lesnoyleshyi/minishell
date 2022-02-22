#include "../../includes/minishell.h"

void	unset(char **arg)
{
	int		flag;
	t_param	*param;

	if (check_valid_param_name(arg) != OK)
		return ;
	param = NULL;
	while (*arg != NULL)
	{
		flag = check_presence_param(&param, *arg);
		if (flag == ENV_PARAM)
			delete_param(&g_common->env, param);
		else if (flag == LOCAL_PARAM)
			delete_param(&g_common->local_param, param);
		++arg;
	}
}
