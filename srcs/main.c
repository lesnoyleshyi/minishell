
#include "minishell.h"

void	ft_execute_pipeline();

int main(int argc, char *argv[], char *envp[])
{
	char	*usr_inp;
	char	*cwd;
	char	*env_var_val;
	int		i;

	argv = NULL;
	envp = NULL;
	if (argc == 2)
	{
		printf("hihi\n");
		ft_execute_pipeline();
		printf("hehe\n");
		return (0);
	}
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
		if (ft_strncmp(usr_inp, "env", 3) == 0)
		{
			i = 0;
			while ((envp + i) && *(envp + i))
			{
				printf("%s\n", *(envp + i));
				i++;
			}
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
