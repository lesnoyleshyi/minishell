#include "../../includes/minishell.h"

/**
 * This function returns the first character after the parameter name.
 * If character is not equal to INIT_PARAM hence syntax error
 */

char	check_param_name(char *str)
{
	while (*str != '\0' && *str != BOTTOM_LINE && ft_isalnum(*str) == 1)
		str++;
	return (*str);
}
