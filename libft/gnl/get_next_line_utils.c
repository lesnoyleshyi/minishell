/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 20:26:55 by drayl             #+#    #+#             */
/*   Updated: 2021/10/20 20:26:57 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	checking_new_line(const char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (0);
		str++;
	}
	return (1);
}

char	*get_old_string(char *old_string)
{
	char	str[BUFFER_SIZE + 1];
	char	*str1;
	int		i;
	int		j;

	i = -1;
	while (old_string[++i] && old_string[i] != '\n')
		str[i] = old_string[i];
	if (old_string[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	str1 = (char *) malloc((i + 1) * sizeof(char));
	if (!str1)
		return (str1);
	j = -1;
	while (++j <= i)
		str1[j] = str[j];
	j = -1;
	while (old_string[i + ++j])
		old_string[j] = old_string[i + j];
	while (old_string[j])
		old_string[j++] = '\0';
	return (str1);
}

int	get_size_new_string(const char *str, const char *buff)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
		i++;
	j = 0;
	while (buff[j] && buff[j] != '\n')
		j++;
	if (buff[j] == '\n')
		j++;
	return (i + j);
}

char	*refill_string(char *str, const char *buff, char *old_string)
{
	char	*new_str;
	int		i;
	int		j;
	int		size;

	size = get_size_new_string(str, buff);
	new_str = (char *)(malloc((size + 1) * sizeof(char)));
	if (!new_str)
		return (new_str);
	i = -1;
	while (str[++i])
		new_str[i] = str[i];
	j = -1;
	while (i + ++j < size)
		new_str[i + j] = buff[j];
	new_str[size] = '\0';
	i = -1;
	while (buff[++i + j])
		old_string[i] = buff[i + j];
	old_string[i] = '\0';
	free(str);
	return (new_str);
}
