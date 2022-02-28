/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_abs_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 23:40:07 by stycho            #+#    #+#             */
/*   Updated: 2022/02/21 23:40:08 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "sys/stat.h"

//Frees all members in array and array itself
void	free_arr(char **paths_arr);

//Checks whether object pointed to by pathname is directory or not.
//Returns 1 if pathname points to directory,
//Returns 0 if pathname points to other type (regular file, socket, pipe, etc).
int		is_directory(char *pathname);

//Searches full path to binary in $PATH
//*
//Returns "<path_prefix> + / + pathname" in case of success
//Returns "command not found" in case binary not found in $PATH
//to handle this error like bash does.
char	*get_abs_path_to_binary(char *pathname);

char	*get_abs_path_to_binary(char *pathname)
{
	char	**paths_arr;
	char	*pathname_w_slash;
	char	*abs_path;
	int		i;

	if (pathname == NULL || ft_strchr(pathname, '/') != NULL)
		return (pathname);
	i = -1;
	//todo по чеклисту тут после unset PATH должно ломаться и выдавать
	// no such file or directory
	paths_arr = ft_split(getenv("PATH"), ':');
	pathname_w_slash = ft_strjoin("/", pathname);
	while (paths_arr != NULL && paths_arr[++i] != NULL)
	{
		abs_path = ft_strjoin(paths_arr[i], pathname_w_slash);
		if (access(abs_path, X_OK) == 0)
		{
			free_arr(paths_arr);
			free(pathname_w_slash);
			return (abs_path);
		}
		free(abs_path);
	}
	free_arr(paths_arr);
	free(pathname_w_slash);
	return ("command not found");
}

void	free_arr(char **paths_arr)
{
	int	i;

	i = -1;
	while (paths_arr != NULL && paths_arr[++i] != NULL)
		free(paths_arr[i]);
	free(paths_arr);
}

int	is_directory(char *pathname)
{
	struct stat	path_stat;

	stat(pathname, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}
