/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funcs2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 20:18:52 by stycho            #+#    #+#             */
/*   Updated: 2022/02/02 20:18:54 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_export(char *cmd_w_args[])
{
	if (cmd_w_args == NULL)
		exit(1);
	printf("export built-in is under development\n");
	exit(0);
}

void	ft_unset(char *cmd_w_args[])
{
	if (cmd_w_args == NULL)
		exit(1);
	printf("unset built-in is under development\n");
	exit(0);
}

void	ft_env(void)
{
	printf("env builtin is under development\n");
	exit(0);
}

void	ft_exit(char *cmd_w_args[])
{

	if (cmd_w_args[1] != NULL)
		exit(ft_atoi(cmd_w_args[1]));
	else
		exit(0);
}
