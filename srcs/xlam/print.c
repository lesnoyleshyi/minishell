/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 00:13:10 by drayl             #+#    #+#             */
/*   Updated: 2022/02/20 00:13:11 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_param(t_param *param)
{
	while (param != NULL)
	{
		printf("%s=%s\n", param->name, param->value);
		param = param->next;
	}
}

void	print_common_param(void)
{
	if (g_common == NULL)
		return ;
	printf("   --- ENV ---   \n");
	print_param(g_common->env);
	printf("   --- LOCAL ---   \n");
	print_param(g_common->local_param);
}

void	print_list(t_list *list)
{
	while (list != NULL)
	{
		printf("lst -> %s\n", list->content);
		list = list->next;
	}
}

void	print_data(t_data *data)
{
	t_file	*file;

	if (data == NULL)
		return ;
	printf("------------------------\n");
	while (data != NULL)
	{
		printf("%p\n", data);
		file = data->file;
		printf("FILES\n");
		while (file != NULL)
		{
			printf("%s %d\n", file->name, file->mod);
			file = file->next;
		}
		printf("COMMAND\n");
		print_array_string(data->command);
		printf("PARAM\n");
		print_param(data->param_list);
		data = data->next;
	}
	printf("------------------------\n");
}

void	print_array_string(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = -1;
	while (array[++i] != NULL)
		printf("%s\n", array[i]);
}
