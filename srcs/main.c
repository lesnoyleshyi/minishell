
#include "../includes/minishell.h"
//delete
//#include "data/data.c"
//#include "data/string_array.c"
//#include "data/file.c"
//#include "data/list.c"
//#include "data/param.c"
//#include "data/common.c"
//#include "string/get_substr.c"
//#include "xlam/div.c"
//#include "string/get_unsubstr.c"
//#include "string/insert_str.c"
//#include "string/remove_all_quote.c"
//#include "string/multi_join.c"
//#include "utils/first_parser.c"
//#include "utils/second_parser.c"
//#include "utils/replace_param.c"
//#include "files/search_in_file_name.c"
//#include "files/search_out_file_name.c"
//#include "checks/check_get_param.c"
//#include "checks/check_spec_sym.c"
//#include "checks/check_init_param.c"
//#include "checks/check_function.c"
//#include "checks/check_input_file.c"
//#include "checks/check_output_file.c"
//#include "checks/check_determinate.c"
//#include "xlam/print.c"
//delete

int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	*data;

	signal(SIGINT, ft_clear_input);
	if (argc || argv)
		;
	g_common = init_common_data((const char **)envp);
//	print_common_param();
	data = NULL;
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL) {
			printf("Goi has pressed Ctrl-D\n");
			return (0);
		}

//		printf("%s\n", input);
		data = init_data(input);
		if (data != NULL && data->command != NULL)
			choice_builtin(data, check_function(data->command[0]));
//		printf("\nPRINT DATA\n");
//		print_data(data);
//		printf("END OF DATA\n");
		ft_execute_pipeline(data, envp);
		destroy_data(&data);
		add_history(input);
		free(input);
	}
}
