#include "../../includes/minishell.h"

/**
 * This function removes the passed string and returns NULL
 */

char	*remove_string(char *str)
{
	if (str != NULL)
		free(str);
	return (NULL);
}
