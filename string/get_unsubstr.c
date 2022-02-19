/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_unsubstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 00:03:56 by drayl             #+#    #+#             */
/*   Updated: 2022/02/20 00:03:58 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * This function returns a string with no elements
 * enclosed between indexes "start"(inclusive) and
 * "end"(exclusive) then deletes the previous string
 */

char	*get_unsubstr(char *str, size_t start, size_t end)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (str == NULL)
		return (NULL);
	res = malloc(sizeof (char) * (start + ft_strlen(str) - end + 1));
	if (res == NULL)
		return (NULL);
	i = -1;
	while (str[++i] != '\0' && i < start)
		res[i] = str[i];
	j = end;
	while (str[j] != '\0')
		res[i++] = str[j++];
	res[i] = '\0';
	free(str);
	return (res);
}
