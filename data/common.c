#include "../includes/minishell.h"

/**
 * This function converts a two-dimensional array
 * "envp" to a list of elements of type "t_param"
 */

static t_param *init_env(const char **envp)
{
	int		i;
	t_param	*new;
	t_param	*begin;

	i = -1;
	while (envp[++i])
	{
		new = init_param(envp[i]);
		if (new == NULL)
			return (NULL);
		add_param(&begin, new);
	}
	return (begin);
}

/**
 * This function initializes general
 * information about environment variables
 */

t_common	*init_common_data(const char **envp)
{
	t_common	*element;

	element = (t_common *)malloc(sizeof (t_common));
	element->env = init_env(envp);
	element->err_number = 0;
	return (element);
}