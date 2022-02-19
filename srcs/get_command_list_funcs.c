
#include "minishell.h"

void	ft_get_command_list(t_data **command_list)
{
	t_file	*last_cmd_file_list;

	*command_list = (t_data *)malloc(sizeof(t_data) * 3);
	if (*command_list == NULL)
	{
		printf("Can't allocate memory for command list\n");
		exit(-1);
	}

	last_cmd_file_list = (t_file *) malloc(sizeof(t_file));

	last_cmd_file_list->mod = E_APPEND;
	last_cmd_file_list->name = ft_strdup("ahah.txt");
	last_cmd_file_list->next = NULL;

	(*command_list)->file = NULL;
	(*command_list)->next = &(*command_list)[1];
//	(*command_list)->next = NULL;
	(*command_list)->command = ft_split("/bin/ls -lA", ' ');

	(*command_list + 1)->file = NULL;
	(*command_list + 1)->next = &(*command_list)[2];
	(*command_list + 1)->command = ft_split("/usr/bin/grep \\.", ' ');

	(*command_list + 2)->file = last_cmd_file_list;
	(*command_list + 2)->next = NULL;
	(*command_list + 2)->command = ft_split("/bin/cat -e", ' ');
}
