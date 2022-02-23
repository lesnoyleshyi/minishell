#include "../../includes/minishell.h"

int	check_common(void)
{
	return (g_common->env == NULL || g_common->home == NULL
			|| g_common->history_file == NULL || g_common->pwd == NULL);
}