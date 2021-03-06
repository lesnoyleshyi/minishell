/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 05:52:17 by drayl             #+#    #+#             */
/*   Updated: 2022/02/24 05:52:19 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This function checks if there is '\n' in
 * the string and if it is, replaces it with '\0'
 */

static void	remove_new_line(char *str)
{
	while (*str != '\0' && *str != '\n')
		++str;
	*str = '\0';
}

/**
 * This function reads the history from the history file
 */

void	read_old_history(void)
{
	int		fd;
	char	*command;

	fd = open(g_common->history_file, O_RDONLY | O_CREAT, 00644);
	if (fd < 0)
		return ;
	command = get_next_line(fd);
	while (command != NULL)
	{
		remove_new_line(command);
		add_history(command);
		free(command);
		command = get_next_line(fd);
	}
	close(fd);
}

/**
 * This function completes the history file when the program exits.
 */

void	add_new_history(void)
{
	int		fd;
	t_list	*begin;

	begin = g_common->history;
	fd = open(g_common->history_file, O_WRONLY | O_CREAT | O_APPEND, 00644);
	if (fd < 0)
		return ;
	while (begin != NULL)
	{
		write(fd, begin->content, ft_strlen(begin->content));
		if (*(begin->content) != '\0')
			write(fd, "\n", 1);
		remove_first_element(&begin);
	}
	close(fd);
}
