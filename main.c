
#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	char	*usr_inp;
	char	*cwd;
	char	*env_var_val;

	argc = 0;
	argv = NULL;
	envp = NULL;
//	while (*envp)
//	{
//		printf("%s\n", *envp);
//		envp += 1;
//	}
//	printf("\nthat's all\n");
	while (1)
	{
		usr_inp = readline("shalom goi$ ");

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
			free(usr_inp);
			continue ;
		}
		if (ft_strncmp(usr_inp, "echo $", 6) == 0)
		{
			env_var_val = getenv(usr_inp + 6);
			printf("%s\n", env_var_val);
		}
		else
		{
			printf("Look: goi said \"%s\"\n", usr_inp);
			if (ft_strncmp(usr_inp, "exit", 4) == 0)
				break;
		}
		free(usr_inp);
	}
	free(usr_inp);
	return 0;
}
