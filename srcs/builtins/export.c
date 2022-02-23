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

static void	export_env_param(t_param *element, t_param *param)
{
	if (param->value != NULL)
	{
		if (element->value != NULL)
			free(element->value);
		element->value = param->value;
	}
	param->value = NULL;
	destroy_param(&param);
}

static void	export_local_param(t_param *element, t_param *param)
{
	if (param->value == NULL)
	{
		param->value = element->value;
		element->value = NULL;
	}
	add_param(&(g_common->env), param);
	delete_param(&(g_common->local_param), element);
}

void	export(char **arg)
{
	t_param	*param;
	t_param	*element;
	int		flag;

	if (*arg == NULL)
	{
		print_export();
		return ;
	}
	if (check_valid_param_name(arg) != OK)
		return ;
	element = NULL;
	while (*arg != NULL)
	{
		param = init_param(*arg);
		flag = check_presence_param(&element, param->name);
		if (flag == NEW_PARAM)
			add_param(&(g_common->env), param);
		else if (flag == ENV_PARAM)
			export_env_param(element, param);
		else if (flag == LOCAL_PARAM)
			export_local_param(element, param);
		++arg;
	}
}
