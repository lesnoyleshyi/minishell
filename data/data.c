
#include "../includes/minishell.h"

/**
 * This function checks if the element is space
 */

static int	check_is_space(char ch)
{
	return ((ch == ' ') || ch == '\n' || ch == '\t'
			|| ch == '\r' || ch == '\f' || ch == '\v');
}



t_list *first_pars(const char *line)
{
	t_list	*begin;
	size_t	start;
	size_t	end;
	char	flag;

	end = 0;
	start = 0;
	while (line[start] != '\0')
	{
		flag = SPACE;
		while (check_is_space(line[start]))
			start++;
		if (line[start] == QUOTE || line[start] == QUOTE2)
			flag = line[start++];
		end = start;
		while (line[end] != '\0' || line[end] != flag)
			++end;

	}
}

t_data	*init_data(const char *line) {
	t_data	*data;

	data = (t_data *) malloc(sizeof(t_data));



	return (data);
}
