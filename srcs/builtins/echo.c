#include "../../includes/minishell.h"

void	echo(char **arg)
{
	int	n;

	n = 0;
	if (*arg != NULL && ft_strcmp(*arg, "-n") == 0)
	{
		n = 1;
		++arg;
	}
	while (*arg != NULL)
	{
		write(1, *arg, ft_strlen(*arg));
		++arg;
		if (*arg != NULL)
			write(1, " ", 1);
	}
	if (n == 0)
		write(1, "\n", 1);
}
