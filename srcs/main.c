/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:03:04 by stycho            #+#    #+#             */
/*   Updated: 2022/02/03 20:03:06 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_pipeline(t_s_cmd *command_list);
void	ft_get_command_list(t_s_cmd **command_list);

int main(int argc, char *argv[], char *envp[])
{
	char	*usr_inp;
	t_s_cmd	*command_list;

	if (argc || argv || envp)
		argc += 0;
	while (1)
	{
		usr_inp = readline("shalom goi$ ");
		if (usr_inp == NULL)
		{
			printf("Goi has pressed Ctrl-D\n");
			return (0);
		}
		add_history(usr_inp);
		ft_get_command_list(&command_list);
		ft_execute_pipeline(command_list);
	}
	free(usr_inp);
	return 0;
}
