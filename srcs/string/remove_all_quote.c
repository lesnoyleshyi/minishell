/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_all_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 00:04:13 by drayl             #+#    #+#             */
/*   Updated: 2022/02/20 00:04:14 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This function increments the index "k" by 1
 * and sets the new value of the variable "flag"
 */

static void	update_value(int *k, char *flag, char new_flag)
{
	++(*k);
	*flag = new_flag;
}

/**
 * This function strips the string of any quotes
 */

void	remove_all_quote(char *str)
{
	int		i;
	int		k;
	char	flag;

	i = 0;
	k = 0;
	flag = SPACE;
	if (str == NULL)
		return ;
	while (str[i] != '\0')
	{
		if ((str[k] == QUOTE || str[k] == QUOTE2) && flag == SPACE)
			update_value(&k, &flag, str[k]);
		else if ((str[k] == flag && flag != SPACE))
			update_value(&k, &flag, SPACE);
		else
			str[i++] = str[k++];
	}
}
