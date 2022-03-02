/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 23:13:17 by stycho            #+#    #+#             */
/*   Updated: 2022/03/01 23:13:19 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//todo личат пустые комманды(которые просто энтером отбиваются)
//todo ls $popka не норм, ls '' норм
//todo личит  unset
//todo не даёт unset $PATH - синтакс еррор выдаёт (баш, кстати, тоже не даёт, только ошибка другая выводится - не фиксим)
//todo если в хередок сунуть $USERABUSER, выведет значение этой переменной, а должен ничего
//todo echo $? даёт лик равный значению этой переменной
//todo  el=$(ruby -e "puts (-10000..10000).to_a.shuffle.join(' ')) даёт лики  - el и ruby(
#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	*data;

	(void)argc;
	(void)argv;
	g_common = init_common_data(envp);
	if (check_common() == TRUE)
		g_common = destroy_common_date();
	read_old_history();
	data = NULL;
	while (TRUE)
	{
		init_signal_handling(main_handler);
		input = readline("minishval'$ ");
		if (input == NULL)
			b_exit(g_common->err_number, NOT_IN_PIPELINE);
		ft_lstadd_back(&(g_common->history), ft_lstnew(input));
		data = init_data(input);
		execute(data);
		destroy_data(&data);
		if (*input != '\0')
			add_history(input);
	}
	add_new_history();
	return (g_common->err_number);
}
