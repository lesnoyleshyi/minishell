/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_substr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 00:03:50 by drayl             #+#    #+#             */
/*   Updated: 2022/02/20 00:03:52 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This function creates a substring from the source string
 * from index {start} (inclusive) to index {end} (exclusive)
 */

char	*get_substr(const char *str, size_t start, size_t end)
{
	size_t	i;
	char	*substr;

	substr = malloc(sizeof (char) * (end - start + 1));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (str[start + i] != '\0' && start + i < end)
	{
		substr[i] = str[start + i];
		++i;
	}
	substr[i] = '\0';
	return (substr);
}

char	*get_substr_for_value(const char *str, size_t start, size_t end)
{
	if (start >= end && (start == 0 || str[start - 1] != INIT_PARAM))
		return (NULL);
	return (get_substr(str, start, end));
}
