
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
//#include "utils/history.c"
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
//#include "checks/check_param_name.c"
//#include "checks/check_presence_param.c"
//#include "builtins/unset.c"
//#include "builtins/export.c"
//#include "builtins/cd.c"
//delete

int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	*data;

	g_common = NULL;
	if (errno == 0)
	signal(SIGINT, ft_clear_input);
	if (argc || argv)
	{};
	g_common = init_common_data((const char **)envp);
	if (check_common() == TRUE)
		g_common = destroy_common_date();
	read_old_history();
//	print_common_param();
	data = NULL;
	while (TRUE)
	{
		input = readline("minishval'$ ");
		if (input == NULL)
		{
			add_new_history();
			b_exit(g_common->err_number, 0);
		}
//		printf("%s\n", input);
		data = init_data(input);
//		printf("\nPRINT DATA\n");
//		print_data(data);
//		printf("END OF DATA\n");
		execute(data);
		destroy_data(&data);
		if (*input != '\0')
			add_history(input);
		ft_lstadd_back(&(g_common->history), ft_lstnew(input));
	}
	add_new_history();
}
