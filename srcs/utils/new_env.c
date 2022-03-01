/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:51:39 by stycho            #+#    #+#             */
/*   Updated: 2022/02/23 19:51:40 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This function returns the number of elements in a linked
 * list of elements of type "t_param" starting from element "begin"
 */

static int	get_size(t_param *begin)
{
	int	size;

	size = 0;
	while (begin != NULL)
	{
		++size;
		begin = begin->next;
	}
	return (size);
}

/**
 * This function takes 2 arguments "name", "value" and returns
 * a concatenated string like "name=value". if the variable "value" is
 * equal to "NULL" then the string will be just a copy of the variable "name"
 */

static char	*get_concat_line(char *name, char *value)
{
	char	*str;
	char	*res;

	if (value == NULL)
		return (ft_strdup(name));
	str = ft_strjoin(name, "=");
	res = ft_strjoin(str, value);
	free(str);
	return (res);
}

/**
 * This function converts the elements of the linked list into strings
 * using the "get_concat_line" function and writes them to the string array
 * "envp" at position "iter". In case of failure, "-1" is returned, if everything
 * went well, it returns the first uninitialized position in the "envp" array
 */

static int	add_param_in_array_string(t_param *param, char **envp, int iter)
{
	while (param != NULL)
	{
		envp[iter] = get_concat_line(param->name, param->value);
		if (envp[iter] == NULL)
			return (-1);
		param = param->next;
		++iter;
	}
	return (iter);
}

/**
 * This function creates an array of strings similar to what
 * the "env" function outputs from the already existing environment
 * variables and the new variables passed to the command as parameters
 */

char	**new_env(t_param *begin)
{
	int		size;
	int		iter;
	char	**envp;

	size = get_size(begin) + get_size(g_common->env) + 1;
	envp = (char **) malloc(size * sizeof (char *));
	if (envp == NULL)
		return (NULL);
	iter = add_param_in_array_string(g_common->env, envp, 0);
	if (iter < 0)
		return (destroy_array(envp));
	iter = add_param_in_array_string(begin, envp, iter);
	if (iter < 0)
		return (destroy_array(envp));
	envp[iter] = NULL;
	return (envp);
}
