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

static t_param	*init_env(const char **envp)
{
	int		i;
	t_param	*new;
	t_param	*begin;

	i = -1;
	begin = NULL;
	while (envp[++i])
	{
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


static char	*get_history_file(t_param *shlvl)
{
	if (shlvl == NULL || shlvl->value == NULL)
		return (NULL);
	return (ft_strjoin(HISTORY_FILE, shlvl->value));
}

/**
 * This function initializes general
 * information about environment variables
 */

t_common	*init_common_data(const char **envp)
{
	t_common	*element;

	element = (t_common *)malloc(sizeof (t_common));
	if (element == NULL)
		return (NULL);
	element->env = init_env(envp);
	element->local_param = NULL;
	element->new_list = NULL;
	element->history = NULL;
	element->err_number = 0;
	if (element->env == NULL)
	{
		free(element);
		return (NULL);
	}
	element->history_file = get_history_file(update_lvl(element->env));
	return (element);
}

/**
 * This function releases the memory
 * allocated for the global variable "common"
 */

void	destroy_common_date(void)
{
	destroy_param(&g_common->env);
	destroy_param(&g_common->local_param);
	free(g_common);
}
