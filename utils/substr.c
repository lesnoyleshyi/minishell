#include "../includes/minishell.h"

/**
 * This function creates a substring from the source string
 * from index {start} (inclusive) to index {end} (exclusive)
 */

char	*get_substr(const char *str, size_t start, size_t end)
{
	int		i;
	char	*substr;

	substr = malloc(sizeof (char) * (end - start + 1));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (str[start + i] != '\0' && start + i < end)
	{
		substr[i] = str[start + i];
		++i;
	}
	substr[i] = '\0';
	return (substr);
}

//char	*update_substr(const char *str, size_t start, size_t end)
//{
//	int		i;
//	char	*substr;
//	char	flag;
//
//	substr = malloc(sizeof (char) * (end - start + 1));
//	if (substr == NULL)
//		return (NULL);
//	i = 0;
//	while (str[start + i] != '\0' && start + i < end)
//	{
//		while (str[start + i] != '\0' && )
//		while (str[start + i] != '\0' && str[start + i] != )
//		substr[i] = str[start + i];
//		++i;
//	}
//	substr[i] = '\0';
//	return (substr);
//}
