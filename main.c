
#include "includes/minishell.h"
//delete
#include "data/data.c"
#include "data/param.c"
#include "data/common.c"
#include "utils/substr.c"
//delete
int main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*cwd;
	char	*env_str;

	while (1)
	{
		input = readline("minishell$ ");
//		env_str = getenv("PATH");
		if (input == NULL)
		{
			printf("Goi has pressed Ctrl-D\n");
			return (0);
		}
		add_history(input);
		if (ft_strncmp(input, "pwd", 3) == 0)
		{
			cwd = getcwd(NULL, 1);
			printf("%s\n", cwd);
			free(cwd);
			continue ;
		}
		printf("Look: goi said \"%s\"\n", input);
		if (ft_strncmp(input, "exit", 4) == 0)
			break;
	}
	free(input);
	return 0;
}
