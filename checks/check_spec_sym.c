/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_spec_sym.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 00:12:40 by drayl             #+#    #+#             */
/*   Updated: 2022/02/20 00:12:41 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * This function checks if a character is special.
 * If yes - returns its identifier,
 * if not returns "E_NOT_SPEC_SYM"
 */

int	check_spec_sym(char c)
{
	write(1, &c, 1);
	if (c == REDIR_IN)
		return (E_REDIR_IN);
	if (c == REDIR_OUT)
		return (E_REDIR_OUT);
	if (c == GET_PARAM)
		return (E_GET_PARAM);
	if (c == INIT_PARAM)
		return (E_INIT_PARAM);
	if (c == PIPE)
		return (E_PIPE);
	return (E_NOT_SPEC_SYM);
}

/**
 * This function checks if a string contains
 * a special character. If yes - returns its
 * identifier and changes the value of "index"
 * to the position of the special character in
 * the string, if not returns "E_NO_SPEC_SYM"
 */

int	check_str_for_spec_sym(const char *str, int *index)
{
	int		res;
	char	flag;

	*index = 0;
	res = check_spec_sym(*str);
	flag = SPACE;
	while (str[++(*index)] != '\0' && res == E_NOT_SPEC_SYM)
	{
		if (flag == SPACE && (str[*index] == QUOTE || str[*index] == QUOTE2))
			flag = str[++(*index)];
		if ((flag == QUOTE2 && str[*index] == QUOTE2)
			|| (flag == QUOTE && str[*index] == QUOTE))
			flag = SPACE;
		if (flag == SPACE || (flag == QUOTE2 && str[*index] == GET_PARAM))
			res = check_spec_sym(str[*index]);
	}
	return (res);
}
