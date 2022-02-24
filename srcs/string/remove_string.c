/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 05:41:39 by drayl             #+#    #+#             */
/*   Updated: 2022/02/24 05:41:40 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This function removes the passed string and returns NULL
 */

char	*remove_string(char *str)
{
	if (str != NULL)
		free(str);
	return (NULL);
}
