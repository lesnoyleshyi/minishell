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

void	ft_execute_pipeline(t_data *command_list);
void	ft_get_command_list(t_data **command_list);

int	execute(t_data *command_list, char *envp[]);

int main(int argc, char *argv[], char *envp[])
{
	char	*usr_inp;
	t_data 	*command_list;

	signal(SIGINT, SIG_IGN);
	if (argc || argv || envp)
		;
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
		execute(command_list, envp);
//		ft_execute_pipeline(command_list);
	}
	free(usr_inp);
	return 0;
}
