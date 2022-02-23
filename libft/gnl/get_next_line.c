/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 20:26:26 by drayl             #+#    #+#             */
/*   Updated: 2021/10/20 20:26:30 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			i;
	char		*str;
	char		buff[BUFFER_SIZE + 1];
	static char	old_string[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE < 1)
		return ((char *)(void *)0);
	str = get_old_string(old_string);
	while (checking_new_line(str))
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i <= 0)
			break ;
		buff[i] = '\0';
		str = refill_string(str, buff, old_string);
	}
	if (!*str)
	{
		free(str);
		return ((char *)(void *)0);
	}
	return (str);
}
