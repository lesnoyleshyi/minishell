/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:56:15 by drayl             #+#    #+#             */
/*   Updated: 2022/02/19 23:56:18 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * This function skips all spaces starting from position "i"
 */

static void	skip_space(const char *str, size_t *i)
{
	while (str[*i] == ' ')
		++(*i);
}

/**
 * This function looks for the index of the
 * next delimiter from position "start"
 */

static size_t	get_end(const char *str, size_t start)
{
	size_t	end;
	char	delimiter;

	delimiter = SPACE;
	end = start;
	while (str[end] != '\0')
	{
		if (delimiter == SPACE && (str[end] == QUOTE || str[end] == QUOTE2))
			delimiter = str[end++];
		if (delimiter == str[end++])
			delimiter = SPACE;
		if (delimiter == SPACE
			&& (check_determinate(str[end]) || check_determinate(str[end - 1])))
			break ;
	}
	return (end);
}

/**
 * This function checks the last element
 * to see if it is empty. If empty - deletes it
 */

static void	check_is_empty_last_content(t_list *begin)
{
	char	*str;
	t_list	*last;

	if (begin == NULL)
		return ;
	last = ft_lstlast(begin);
	str = last->content;
	if (*str == '\0')
		remove_element(&begin, last);
}

/**
 * This function splits the received
 * string into a list of elements
 */

void	first_pars(const char *line, t_list **begin)
{
	size_t	start;
	size_t	end;
	t_list	*new_element;
	char	*string;

	end = 0;
	while (line[end] != '\0')
	{
		start = end;
		skip_space(line, &start);
		end = get_end(line, start);
		string = get_substr(line, start, end);
		new_element = ft_lstnew(string);
		if (new_element == NULL || string == NULL)
		{
			if (string != NULL)
				free(string);
			ft_lstclear(begin, free);
			return ;
		}
		ft_lstadd_back(begin, new_element);
	}
	check_is_empty_last_content(*begin);
}
