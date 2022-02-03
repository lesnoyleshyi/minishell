
#include "minishell.h"

void	ft_get_command_list(t_s_cmd **command_list)
{
	*command_list = (t_s_cmd *)malloc(sizeof(t_s_cmd) * 3);
	if (*command_list == NULL)
	{
		printf("Can't allocate memory for command list\n");
		exit(-1);
	}

	(*command_list)->input = NULL;
	(*command_list)->output = NULL;
	(*command_list)->next = &(*command_list)[1];
//	(*command_list)->next = NULL;
	(*command_list)->cmd_w_args = ft_split("/bin/ls -lA", ' ');

	(*command_list + 1)->input = NULL;
	(*command_list + 1)->output = NULL;
	(*command_list + 1)->next = &(*command_list)[2];
	(*command_list + 1)->cmd_w_args = ft_split("/usr/bin/grep \\.", ' ');

	(*command_list + 2)->input = NULL;
	(*command_list + 2)->output = NULL;
	(*command_list + 2)->next = NULL;
	(*command_list + 2)->cmd_w_args = ft_split("/bin/cat -e", ' ');
}
