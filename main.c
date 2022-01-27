
#include "minishell.h"

int main()
{
	char	*usr_inp;
	char	*cwd;
//	char	*env_str;

	while (1)
	{
		usr_inp = readline("shalom goi$ ");
//		env_str = getenv("PATH");
		if (usr_inp == NULL)
		{
			printf("Goi has pressed Ctrl-D\n");
			return (0);
		}
		add_history(usr_inp);
		if (ft_strncmp(usr_inp, "pwd", 3) == 0)
		{
			cwd = getcwd(NULL, 1);
			printf("%s\n", cwd);
			free(cwd);
			continue ;
		}
		printf("Look: goi said \"%s\"\n", usr_inp);
		if (ft_strncmp(usr_inp, "exit", 4) == 0)
			break;
	}
	free(usr_inp);
	return 0;
}
