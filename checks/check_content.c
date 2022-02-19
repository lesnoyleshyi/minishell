/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 00:12:02 by drayl             #+#    #+#             */
/*   Updated: 2022/02/20 00:12:04 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * This function checks whether the string
 * "str" is a separator or part of a command
 */

int	check_content(const char *str, int flag)
{
	while (*str != '\0')
	{
		if (*str == REDIR_IN)
			return (E_REDIR_IN);
		if (*str == REDIR_OUT)
			return (E_REDIR_OUT);
		if (*str == INIT_PARAM && flag == TRUE)
			return (E_INIT_PARAM);
		if (*str == PIPE)
			return (E_PIPE);
		if (*str == QUOTE || *str == QUOTE2 || *str == GET_PARAM)
			return (E_NOT_SPEC_SYM);
		++str;
	}
	return (E_NOT_SPEC_SYM);
}
