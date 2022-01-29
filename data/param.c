#include "../includes/minishell.h"

/**
 * This function creates a new element of type "t_param"
 * and places it at the end of the list "begin"
 */

void	add_param(t_param **begin, t_param *new)
{
	t_param *element;

	if (begin == NULL || *begin == NULL)
		*begin = new;
	element = *begin;
	while (element->next != NULL)
		element = element->next;
	element->next = new;
}

/**
 * This function finds the required
 * element in the list and removes it.
 */

void	delete_param(t_param **begin, t_param *element)
{
	t_param	*param;

	if (*begin == element)
		*begin = element->next;
	else
	{
		param = *begin;
		while (param != NULL && param->next != element)
			param = param->next;
		if (param != NULL)
			param->next = element->next;
	}
	free(element->name);
	free(element->value);
	free(element);
}

/**
 * This function takes a string like "NAME=VALUE",
 * creates a new element of type t_param and returns it.
 * In case of an error, it returns NULL
 */

t_param	*init_param(const char *str)
{
	t_param	*new;
	size_t	index;

	new = (t_param *) malloc(sizeof (t_param));
	if (new == NULL)
		return (NULL);
	index = 0;
	while (str[index] != '=')
		++index;
	new->name = get_substr(str, 0, index);
	new->value = get_substr(str, index + 1, ft_strlen(str));
	if (new->value == NULL || new->name == NULL)
		return (NULL);
	new->next = NULL;
	return (new);
}