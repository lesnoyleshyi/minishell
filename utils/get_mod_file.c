/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mod_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:57:27 by drayl             #+#    #+#             */
/*   Updated: 2022/02/19 23:57:31 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * This function checks with which modifier the file should be opened.
 */

int	get_mod_file(t_list **begin, t_list **element, int mod)
{
	if (*(*element)->content != REDIR_IN && *(*element)->content != REDIR_OUT)
		return (mod);
	if (*(*element)->content == REDIR_IN)
		mod = E_HEREDOC;
	else if (*(*element)->content == REDIR_OUT)
		mod = E_APPEND;
	*element = remove_element(begin, *element);
	return (mod);
}
