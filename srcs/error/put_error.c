/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:17:45 by stycho            #+#    #+#             */
/*   Updated: 2022/03/01 15:17:46 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	put_error_param_name(char ch)
{
	write(2, NAME, ft_strlen(NAME));
	write(2, ": ", 2);
	write(2, ERR_INIT_PARAM, ft_strlen(ERR_INIT_PARAM));
	write(2, " \'", 2);
	write(2, &ch, 1);
	write(2, "\'\n", 2);
	g_common->err_number = 258;
}

void	put_error_id_for_unset(char *arg)
{
	write(2, NAME, ft_strlen(NAME));
	write(2, ": ", 2);
	write(2, C_UNSET, ft_strlen(C_UNSET));
	write(2, ": ", 2);
	write(2, "\'", 1);
	write(2, arg, ft_strlen(arg));
	write(2, "\': ", 3);
	write(2, INVALID_ARG_FOR_UNSET, ft_strlen(INVALID_ARG_FOR_UNSET));
	write(2, "\n", 1);
	g_common->err_number = 1;
}

void	put_error_cd(char *dir_name, char *message, int oldpwd_flag)
{
	write(2, NAME, ft_strlen(NAME));
	write(2, ": ", 2);
	write(2, C_CD, ft_strlen(C_CD));
	write(2, ": ", 2);
	write(2, dir_name, ft_strlen(dir_name));
	if (oldpwd_flag == FALSE)
		write(2, ":", 1);
	write(2, " ", 1);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	g_common->err_number = 1;
}

void	memory_error(void)
{
	write(2, NAME, ft_strlen(NAME));
	write(2, ": ", 2);
	write(2, MEM_ERR, ft_strlen(MEM_ERR));
	write(2, "\n", 1);
	exit(TOTAL_PIZDEC);
}

int	syntax_error(char *substr)
{
	write(2, NAME, ft_strlen(NAME));
	write(2, ": ", 2);
	write(2, SYN_ERR, ft_strlen(SYN_ERR));
	write(2, " \'", 2);
	write(2, substr, ft_strlen(substr));
	write(2, "\'\n", 2);
	g_common->err_number = 258;
	return (SYNTAX_ERROR);
}
