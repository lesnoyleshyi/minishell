
#include "../../includes/minishell.h"

void	ft_get_command_list(t_data **command_list)
{
	t_file	*in_file_1;
	t_file	*in_file_2;
	t_file	*in_file_3;
	t_file	*out_file_1;
	t_file	*out_file_2;
	t_file	*out_file_3;

	*command_list = (t_data *)malloc(sizeof(t_data) * 3);
	if (*command_list == NULL)
	{
		printf("Can't allocate memory for command list\n");
		exit(-1);
	}

	out_file_1 = (t_file *) malloc(sizeof(t_file));
	out_file_2 = (t_file *) malloc(sizeof(t_file));
	out_file_3 = (t_file *) malloc(sizeof(t_file));

	out_file_3->mod = E_APPEND;
	out_file_3->name = ft_strdup("out_file3.txt");
	out_file_3->next = NULL;

	out_file_2->mod = E_OUT;
	out_file_2->name = ft_strdup("out_file2.txt");
	out_file_2->next = out_file_3;

	out_file_1->mod = E_OUT;
	out_file_1->name = ft_strdup("out_file1.txt");
	out_file_1->next = out_file_2;

	in_file_1 = (t_file *) malloc(sizeof(t_file));
	in_file_2 = (t_file *) malloc(sizeof(t_file));
	in_file_3 = (t_file *) malloc(sizeof(t_file));

	in_file_3->mod = E_IN;
	in_file_3->name = ft_strdup("in_file3.txt");
	in_file_3->next = NULL;

	in_file_2->mod = E_IN;
	in_file_2->name = ft_strdup("in_file2.txt");
	in_file_2->next = in_file_3;

	in_file_1->mod = E_IN;
	in_file_1->name = ft_strdup("in_file1.txt");
	in_file_1->next = in_file_2;

	out_file_3->next = in_file_1;

	(*command_list)->file = NULL;
	(*command_list)->next = &(*command_list)[1];
//	(*command_list)->next = NULL;
	(*command_list)->command = ft_split("/bin/ls -lA", ' ');

	(*command_list + 1)->file = NULL;
	(*command_list + 1)->next = &(*command_list)[2];
	(*command_list + 1)->command = ft_split("/usr/bin/grep \\.", ' ');

	(*command_list + 2)->file = out_file_1;
	(*command_list + 2)->next = NULL;
	(*command_list + 2)->command = ft_split("/bin/cat -e", ' ');
}
