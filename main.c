
#include "minishell.h"

int main()
{
	char	*usr_inp;
//	char	*env_str;

	while (1)
	{
		usr_inp = readline("shalom goi$ ");
//		env_str = getenv("PATH");
		printf("Look: goi said \"%s\"\n", usr_inp);
		if (ft_strncmp(usr_inp, "exit\n", 4) == 0)
			break;
	}
	free(usr_inp);
	return 0;
}
