
#include "minishell.h"

void	ft_get_command_list(t_s_cmd **command_list)
{
	t_file	*in_files_list;
	t_file	*out_files_list;

	in_files_list = NULL;
	out_files_list = NULL;

	*command_list = (t_s_cmd *)malloc(sizeof(t_s_cmd) * 3);
	if (*command_list == NULL)
	{
		printf("Can't allocate memory for command list\n");
		exit(-1);
	}

	in_files_list = (t_file *) malloc(sizeof(t_file) * 3);
	in_files_list->name = ft_strdup("file0");
	(in_files_list + 1)->name = ft_strdup("file1");
	(in_files_list + 2)->name = ft_strdup("file2");
	in_files_list->next = in_files_list + 1;
	(in_files_list + 1)->next = in_files_list + 2;
	(in_files_list + 2)->next = NULL;
	printf("first arg: %s\n", in_files_list->name);
	printf("second arg: %s\n", (in_files_list + 1)->name);
	printf("third arg: %s\n", (in_files_list + 2)->name);

	out_files_list = (t_file *) malloc(sizeof(t_file) * 2);
	(out_files_list)->name = ft_strdup("file3");
	(out_files_list + 1)->name = ft_strdup("file4");
	(out_files_list)->next = out_files_list + 1;
	(out_files_list + 1)->next = NULL;

	(*command_list)->input = in_files_list;
	(*command_list)->output = out_files_list;
//	(*command_list)->output = NULL;
//	(*command_list)->next = &(*command_list)[1];
	(*command_list)->next = NULL;
	(*command_list)->cmd_w_args = ft_split("/usr/bin/ls -lA", ' ');

	//	below code is for second command
	(*command_list + 1)->input = NULL;
	(*command_list + 1)->output = NULL;
	(*command_list + 1)->next = &(*command_list)[2];
	(*command_list + 1)->cmd_w_args = ft_split("/usr/bin/grep \\.", ' ');


//	below code is for third command
	(*command_list + 2)->input = NULL;
	(*command_list + 2)->output = NULL;
	(*command_list + 2)->next = NULL;
	(*command_list + 2)->cmd_w_args = ft_split("/usr/bin/cat -e", ' ');

	printf("Got args successfully\n");
}
