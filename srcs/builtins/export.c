#include "../../includes/minishell.h"

static t_param	*get_min_param(t_param *limiter)
{
	t_param	*element;
	t_param	*min;

	element = g_common->env;
	min = NULL;
	while (element != NULL)
	{
		if (limiter != NULL && ft_strcmp(limiter->name, element->name) >= 0)
		{
			element = element->next;
			continue ;
		}
		if (min == NULL || ft_strcmp(min->name, element->name) > 0)
			min = element;
		element = element->next;
	}
	return (min);
}

static void	print_export(void)
{
	t_param	*param;

	param = get_min_param(NULL);
	while (param != NULL)
	{
		if (param->value != NULL)
			printf("declare -x %s=\"%s\"\n", param->name, param->value);
		else
			printf("declare -x %s\n", param->name);
		param = get_min_param(param);
	}
}

static int	check_presence_param(t_param **element, char *name)
{
	if (name == NULL)
		return (0);
	*element = g_common->env;
	while (*element != NULL)
	{
		if (ft_strcmp((*element)->name, name) == 0)
			return (1);
		*element = (*element)->next;
	}
	*element = g_common->local_param;
	while (*element != NULL)
	{
		if (ft_strcmp((*element)->name, name) == 0)
			return (2);
		*element = (*element)->next;
	}
	return (0);
}

static void	add_param_for_env(t_param **new_list, t_param *param)
{
	int		flag;
	t_param	*element;

	if (param == NULL)
		return ;
	flag = check_presence_param(&element, param->name);
	if (flag == 0)
		add_param(new_list, param);
	else if (flag == 1)
	{
		if (element->value != NULL)
			free(element->value);
		element->value = param->value;
		free(param->name);
		free(param);
	}
	else
	{
		delete_param(&g_common->local_param, element);
		add_param(new_list, param);
	}
}

void	export(char **arg)
{
	t_param	*param;
	t_param	*new_list;
	int		flag;

	if (*arg == NULL)
	{
		print_export();
		return ;
	}
	new_list = NULL;
	flag = OK;
	while (*arg != NULL && flag == OK)
	{
		param = init_param(*arg);
		if (param == NULL)
			flag = MEMORY_ERROR;
		else if (param->name == NULL)
			flag = SYNTAX_ERROR;
		add_param_for_env(&new_list, param);
		++arg;
	}
	if (flag != OK)
		destroy_param(&new_list);
	add_param(&g_common->env, new_list);
}
