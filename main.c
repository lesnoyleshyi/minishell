
#include "minishell.h"

int main()
{
	char	*usr_inp;

	usr_inp = readline("shalom goi$ ");
	printf("Look: goi said %s\n", usr_inp);
	free(usr_inp);
	return 0;
}
