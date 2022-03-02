/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 04:48:13 by drayl             #+#    #+#             */
/*   Updated: 2022/03/02 04:48:15 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_for_norminette(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_common = init_common_data(envp);
	if (check_common() == TRUE)
		g_common = destroy_common_date();
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	*data;

	init_for_norminette(argc, argv, envp);
	read_old_history();
	data = NULL;
	while (TRUE)
	{
		init_signal_handling(main_handler);
		input = readline("minishval'$ ");
		if (input == NULL)
			b_exit(g_common->err_number, NOT_IN_PIPELINE);
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		ft_lstadd_back(&(g_common->history), ft_lstnew(input));
		data = init_data(input);
		if (data == NULL)
			continue ;
		execute(data);
		destroy_data(&data);
		add_history(input);
	}
}
