/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:51:39 by stycho            #+#    #+#             */
/*   Updated: 2022/02/23 19:51:40 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Creates null-terminated array of pointers to strings,
//where every string is in form "key=val".
char **param_list_to_arr(t_param *param_list);

//Concatenates string in form "key=val" taking values from param's fields
char *param_to_string(t_param *param);

//Returns length of linked list of t_param structs
size_t	param_list_len(t_param *param);

//Returns length of null-terminated array that consist of pointers to strings
size_t	char_p_arr_len(char **arr);

//Returns pointer to char** array of env variables.
//Result array includes variables from env + that was passed to command in form
//var1=val1 var2=val2 command
char **new_env(char *envp[], t_param *param_list);

char **new_env(char *envp[], t_param *param_list)
{
	size_t	old_arr_len;
	size_t	param_count;
	size_t	i;
	char	**param_arr;
	char	**new_env;

	if (param_list == NULL)
		return (envp);
	old_arr_len = char_p_arr_len(envp);
	param_count = param_list_len(param_list);
	new_env = (char **) malloc(sizeof(char *) * old_arr_len + param_count);
	param_arr = param_list_to_arr(param_list);
	if (new_env == NULL || param_arr == NULL)
		return (envp);
	i = -1;
	while (++i < old_arr_len)
		new_env[i] = envp[i];
	i = -1;
	while (++i < param_count)
		new_env[old_arr_len + i] = param_arr[i];
	return (new_env);
}

char **param_list_to_arr(t_param *param_list)
{
	char	**param_arr;
	size_t	param_count;
	int		i;

	if (param_list == NULL)
		return (NULL);
	param_count = param_list_len(param_list);
	param_arr = (char **)malloc(sizeof(char *) * param_count);
	i = 0;
	while (param_list + i != NULL)
	{
		param_arr[i] = param_to_string(param_list + i);
		if (param_arr[i++] == NULL)
			break ;
	}
	param_arr[i] = NULL;
	return (param_arr);
}

char *param_to_string(t_param *param)
{
	char	*name_plus_eq;
	char	*name_plus_eq_plus_val;

	name_plus_eq = ft_strjoin(param->name, "=");
	if (name_plus_eq == NULL)
		return (NULL);
	name_plus_eq_plus_val = ft_strjoin(name_plus_eq, param->value);
	free(name_plus_eq);
	return (name_plus_eq_plus_val);
}

size_t	param_list_len(t_param *param)
{
	size_t	len;

	len = 0;
	while (param + len != NULL)
		len++;
	return (len);
}

size_t	char_p_arr_len(char **arr)
{
	size_t	len;

	len = 0;
	while (arr[len] != NULL)
		len++;
	return (len);
}
