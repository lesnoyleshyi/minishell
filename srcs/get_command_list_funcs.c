
#include "minishell.h"

void	ft_get_command_list(t_s_cmd **command_list)
{
	char	**inp_files_list;
	char	**out_files_list;
	char	*inp_files[] = {"file0", "file1", "file2", NULL};
	char	*out_files[] = {"file3", "file4", NULL};
	int		i;
	int 	j;
	int		len;

	*command_list = (t_s_cmd *)malloc(sizeof(t_s_cmd) * 3);
	if (*command_list == NULL)
	{
		printf("Can't allocate memory for command list\n");
		exit(-1);
	}

	inp_files_list = (char **) malloc(sizeof(char *) * 4);
	if (!inp_files_list)
	{
		printf("Error allocating memory");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < 3)
	{
		j = -1;
		len = (int)ft_strlen(inp_files[i]);
		inp_files_list[i] = (char *) malloc(sizeof(char) * len + 1);
		while (++j < (int)ft_strlen(inp_files[i]))
			inp_files_list[i][j] = inp_files[i][j];
		inp_files_list[i][j] = '\0';
	}
	inp_files_list[i] = NULL;
//	printf("got input\n");
	out_files_list = (char **) malloc(sizeof(char *) * 3);
	i = -1;
	while (++i < 2)
	{
		j = -1;
		len = (int) ft_strlen(out_files[i]);
		out_files_list[i] = (char *) malloc(sizeof(char) * len + 1);
		while (++j < len)
			out_files_list[i][j] = out_files[i][j];
		out_files_list[i][j] = '\0';
	}
	out_files_list[i] = NULL;
//	printf("got output\n");
	(*command_list)->input = inp_files_list;
	(*command_list)->output = out_files_list;
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

//	printf("Got args successfully\n");
}
