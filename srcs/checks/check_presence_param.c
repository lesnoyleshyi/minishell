#include "../../includes/minishell.h"

int	check_presence_param(t_param **element, char *name)
{
	if (name == NULL)
		return (NEW_PARAM);
	*element = g_common->env;
	while (*element != NULL)
	{
		if (ft_strcmp((*element)->name, name) == 0)
			return (ENV_PARAM);
		*element = (*element)->next;
	}
	*element = g_common->local_param;
	while (*element != NULL)
	{
		if (ft_strcmp((*element)->name, name) == 0)
			return (LOCAL_PARAM);
		*element = (*element)->next;
	}
	return (NEW_PARAM);
}
