/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:59:00 by drayl             #+#    #+#             */
/*   Updated: 2022/02/19 23:59:02 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This function returns the name of the variable
 * and sets the index "end" to the end of
 * this variable in the source string
 */

static size_t	get_end_name(char *str, size_t start)
{
	size_t	end;

	end = start + 1;
	if (str[end] == ERROR_STATUS)
		return (end + 1);
	while (ft_isalnum(str[end]) || str[end] == BOTTOM_LINE)
		end++;
	return (end);
}

/**
 * This function replaces a variable
 * named "name" with its "value"
 */

static char	*replace_name_with_value(char *str, size_t *start)
{
	char	*name;
	char	*value;
	size_t	end;

	end = get_end_name(str, *start);
	name = get_substr(str, (*start) + 1, end);
	if (name == NULL)
		return (NULL);
	str = get_unsubstr(str, *start, end);
	if (str == NULL)
	{
		free(name);
		return (NULL);
	}
	value = get_param_value(name);
	if (value != NULL)
		str = insert_srt(str, value, start);
	else
		--(*start);
	free(name);
	return (str);
}

/**
 * This function replaces all variables with their
 * values and returns to the sink after the change
 */

char	*replace_all_param(char *str)
{
	size_t	start;
	char	determinate;

	if (g_common == NULL || check_get_param(str) == FALSE)
		return (str);
	start = -1;
	determinate = SPACE;
	while (str[++start] != '\0')
	{
		if ((str[start] == QUOTE || str[start] == QUOTE2)
			&& determinate == SPACE)
			determinate = str[start++];
		if (str[start] == GET_PARAM && determinate != QUOTE)
			str = replace_name_with_value(str, &start);
		if (str == NULL)
			return (NULL);
		if (str[start] == determinate)
			determinate = SPACE;
	}
	return (str);
}
