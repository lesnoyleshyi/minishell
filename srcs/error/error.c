
#include "../../includes/minishell.h"

//Prints error message in format "minishval': message: <errno>"
//and returns ret_val.
int	ft_perror_and_return(char *message, int ret_val);

int	ft_perror_and_return(char *message, int ret_val)
{
	write(2, "minishval': ", 12);
	perror(message);
	return (ret_val);
}

void	ft_exit_command_not_found(char *filename)
{
	write(2, "minishval': ", 12);
	write(2, filename, ft_strlen(filename));
	write(2, ": command not found\n", 20);
	exit(127);
}
