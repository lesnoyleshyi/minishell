/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 00:04:05 by drayl             #+#    #+#             */
/*   Updated: 2022/02/20 00:04:07 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * This function inserts the string "substr" into the
 * string "str" at position "index". Deletes the
 * previous variant, sets the pointer to the end of the
 * inserted string on a new line, and returns the result
 */

char	*insert_srt(char *str, char *substr, size_t *index)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (substr == NULL)
		return (str);
	res = malloc((ft_strlen(str) + ft_strlen(substr) + 1));
	if (res == NULL)
		return (NULL);
	i = -1;
	while (str[++i] != '\0' && i < *index)
		res[i] = str[i];
	while (*substr != '\0')
		res[i++] = *(substr++);
	j = *index;
	*index = i - 1;
	while (str[j] != '\0')
		res[i++] = str[j++];
	res[i] = '\0';
	free(str);
	return (res);
}
