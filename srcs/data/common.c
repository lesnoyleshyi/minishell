/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 00:06:05 by drayl             #+#    #+#             */
/*   Updated: 2022/02/20 00:06:07 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * This function converts a two-dimensional array
 * "envp" to a list of elements of type "t_param"
 */

static t_param	*init_env(char **envp)
{
	int		i;
	t_param	*new;
	t_param	*begin;

	i = -1;
	begin = NULL;
	while (envp[++i] != NULL)
	{
		if (check_param_name(envp[i]) == '\0')
			continue ;
		new = init_param(envp[i]);
		if (new == NULL)
		{
			destroy_param(&begin);
			return (NULL);
		}
		add_param(&begin, new);
	}
	return (begin);
}

/**
 * This function increments the "SHLVL"
 * value by 1 and sets the new value
 */

static t_param	*update_lvl(t_param *begin)
{
	t_param	*param;
	int		lvl;

	param = begin;
	while (param != NULL && ft_strcmp(param->name, SH_LVL) != 0)
		param = param->next;
	if (param == NULL)
		return (NULL);
	lvl = ft_atoi(param->value) + 1;
	free(param->value);
	param->value = ft_itoa(lvl);
	return (param);
}

/**
 * This function returns the full name of
 * the file in which the command history is written.
 */

static char	*get_history_file(t_param *shlvl, char *home_path)
{
	char	*buff;
	char	*name;

	if (shlvl == NULL || shlvl->value == NULL)
		return (NULL);
	name = ft_strjoin(home_path, "/");
	if (name == NULL)
		return (NULL);
	buff = ft_strjoin(name, HISTORY_FILE);
	free(name);
	if (buff == NULL)
		return (NULL);
	name = ft_strjoin(buff, shlvl->value);
	free(buff);
	return (name);
}

/**
 * This function initializes general
 * information about environment variables
 */

t_common	*init_common_data(char **envp)
{
	t_common	*element;
	t_param		*param;

	element = (t_common *)malloc(sizeof (t_common));
	if (element == NULL)
		return (NULL);
	element->env = init_env(envp);
	element->local_param = NULL;
	element->new_list = NULL;
	element->history = NULL;
	element->home = NULL;
	element->err_number = 0;
	element->pwd = getcwd(NULL, 0);
	param = element->env;
	while (param != NULL && ft_strcmp(param->name, HOME))
		param = param->next;
	if (param != NULL)
		element->home = ft_strdup(param->value);
	element->history_file = get_history_file(update_lvl(element->env),
			element->home);
	return (element);
}

/**
 * This function releases the memory
 * allocated for the global variable "common"
 */

t_common	*destroy_common_date(void)
{
	if (g_common == NULL)
		return (NULL);
	if (g_common->env != NULL)
		destroy_param(&(g_common->env));
	if (g_common->local_param != NULL)
		destroy_param(&(g_common->local_param));
	if (g_common->new_list != NULL)
		destroy_param(&(g_common->new_list));
	if (g_common->history != NULL)
		remove_all_list(&(g_common->history));
	if (g_common->history_file != NULL)
		free(g_common->history_file);
	if (g_common->pwd != NULL)
		free(g_common->pwd);
	if (g_common->home != NULL)
		free(g_common->home);
	free(g_common);
	memory_error();
	return (NULL);
}
