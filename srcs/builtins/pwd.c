#include "../../includes/minishell.h"

void	pwd(void)
{
	printf("%s\n", getcwd(NULL, 0));
}