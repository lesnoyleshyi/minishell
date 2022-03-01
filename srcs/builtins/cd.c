/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:02:29 by drayl             #+#    #+#             */
/*   Updated: 2022/02/23 13:02:30 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This function creates a variable of type "t_param" with "name"
 * and "value" passed in and adds it to the list of environment variables
 */

static void	add_pwd(char *name, char *value)
{
	t_param	*param;

	param = (t_param *) malloc(sizeof (t_param));
	if (param == NULL)
		return ;
	param->name = ft_strdup(name);
	if (param->name == NULL)
	{
		free(param);
		return ;
	}
	param->value = value;
	add_param(&g_common->env, param);
}

/**
 * This function checks if there is a variable with the "name"
 * field, if there is, then the variable's knowledge of "value"
 * is changed, if not, a new variable is initialized
 * and added to the list of environment variables
 */

static void	update_pwd(char *name, char *value)
{
	int		flag;
	t_param	*param;

	flag = check_presence_param(&param, name);
	if (flag == ENV_PARAM)
	{
		free(param->value);
		param->value = value;
	}
	else
	{
		if (flag == LOCAL_PARAM)
			delete_param(&g_common->local_param, param);
		add_pwd(name, value);
	}
}

/**
 * This function changes the values or initializes
 * the environment variables named "OLDPWD", "PWD" and changes
 * the value for "pwd" stored in the global variable "g_common"
 */

static void	update_all_pwd(void)
{
	update_pwd(OLD_PWD, g_common->pwd);
	g_common->pwd = getcwd(NULL, 0);
	update_pwd(PWD, ft_strdup(g_common->pwd));
}

/**
 * This function changes the current directory
 * to the previous one with subsequent changes
 */

static void	dir_tire(void)
{
	int		flag;
	t_param	*param;

	flag = check_presence_param(&param, OLD_PWD);
	if (flag == NEW_PARAM)
	{
		put_error_cd(OLD_PWD, NOT_SET, TRUE);
		return ;
	}
	else if (flag == LOCAL_PARAM)
		write(1, "\n", 1);
	else if (flag == ENV_PARAM)
	{
		if (chdir(param->value) == -1)
		{
			put_error_cd(param->value, strerror(errno), FALSE);
			return ;
		}
		else
		{
			update_all_pwd();
			pwd();
		}
	}
	g_common->err_number = 0;
}

/**
 * This function changes the current directory depending on the "dir" parameter
 */

void	cd(char *dir)
{
	if (dir != NULL && ft_strcmp(dir, TIRE) == 0)
		dir_tire();
	else
	{
		if (dir == NULL || ft_strcmp(dir, TILDA) == 0)
			dir = g_common->home;
		if (chdir(dir) == -1)
			put_error_cd(dir, strerror(errno), FALSE);
		else
		{
			update_all_pwd();
			g_common->err_number = 0;
		}
	}
}
