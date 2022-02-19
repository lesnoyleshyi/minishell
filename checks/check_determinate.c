/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_determinate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 00:12:10 by drayl             #+#    #+#             */
/*   Updated: 2022/02/20 00:12:12 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * This function checks if a character is a delimiter
 */

int	check_determinate(char c)
{
	if (c == SPACE || c == PIPE || c == REDIR_IN || c == REDIR_OUT)
		return (TRUE);
	return (FALSE);
}
