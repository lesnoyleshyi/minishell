/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 20:16:27 by stycho            #+#    #+#             */
/*   Updated: 2022/02/02 20:16:28 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_builtin(char *cmd_w_args[])
{
	if (ft_strncmp("echo\0", cmd_w_args[0], 5) == 0)
		ft_echo(cmd_w_args);
	if (ft_strncmp("cd\0", cmd_w_args[0], 3) == 0)
		ft_cd(cmd_w_args[1]);
	if (ft_strncmp("pwd\0", cmd_w_args[0], 4) == 0)
		ft_pwd();
	if (ft_strncmp("export\0", cmd_w_args[0], 7) == 0)
		ft_export(cmd_w_args);
	if (ft_strncmp("unset\0", cmd_w_args[0], 7) == 0)
		ft_unset(cmd_w_args);
	if (ft_strncmp("env\0", cmd_w_args[0], 4) == 0)
		ft_env();
	if (ft_strncmp("exit\0", cmd_w_args[0], 5) == 0)
		ft_export(cmd_w_args);
}

void	ft_echo(char *cmd_w_args[])
{
	int	i;
	int	n_flag;

	i = 0;
	if (ft_strncmp(cmd_w_args[1], "-n\0", 3) == 0)
	{
		n_flag = 1;
		i++;
	}
	while (cmd_w_args[++i] != NULL)
		printf("%s ", cmd_w_args[i]);
	if (n_flag == 0)
		printf("\n");
	exit(0);
}

void	ft_cd(const char *path)
{
	if (chdir(path) == -1)
		exit(2);
	exit(0);
}

void	ft_pwd(void)
{
	char	*cur_directory;

	cur_directory = getcwd(NULL, 1);
	printf("%s\n", cur_directory);
	free(cur_directory);
	exit(0);
}