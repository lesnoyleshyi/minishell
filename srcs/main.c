
#include "minishell.h"

void	ft_execute_pipe();
void	ft_execute_pipeline(t_s_cmd *command_list);
void	ft_get_command_list(t_s_cmd **command_list);

int main(int argc, char *argv[], char *envp[])
{
	char	*usr_inp;
	char	*cwd;
	char	*env_var_val;
	int		i;
	t_s_cmd	*command_list;
	t_s_cmd	*dummy;

	argv = NULL;
	envp = NULL;
	if (argc == 2)
	{
		ft_execute_pipe();
		return (0);
	}
	if (argc == 3)
	{
		ft_get_command_list(&command_list);
		dummy = command_list;
		int m = 1;
		while (dummy != NULL)
		{
			int n = 0;
			printf("%d cmd: ", m);
			while ((*dummy).cmd_w_args[n])
			{
				printf("%s ", (*dummy).cmd_w_args[n]);
				n++;
			}
			printf("\n");
			dummy = dummy->next;
			m++;
		}
		ft_execute_pipeline(command_list);
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
