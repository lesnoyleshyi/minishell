#include "../../includes/minishell.h"

static char	*up_strjoin(char *str1, char *str2)
{
	char	*result;

	result = NULL;
	if (str1 == NULL || str2 == NULL)
		return (NULL);
	result = ft_strjoin(str1, str2);
	free(str1);
	return (result);
}

static int	read_text(const char *stop_word, char **result)
{
	char	*text;
	char	*buff;

	if (stop_word == NULL)
		return (MEMORY_ERROR);
	text = ft_strdup("");
	buff = readline("> ");
	while (buff != NULL)
	{
		if (ft_strcmp(buff,stop_word) == 0)
			break ;
		buff = up_strjoin(buff, "\n");
		text = up_strjoin(text, buff);
		free(buff);
		if (text == NULL)
			return (MEMORY_ERROR);
		buff = readline("> ");
	}
	*result = text;
	return (OK);
}

int	read_heredoc(t_data *data)
{
	t_file	*file;

	while (data != NULL)
	{
		file = data->file;
		while (file != NULL)
		{
			if (file->mod == E_HEREDOC)
			{
				if (file->name == NULL)
					return (SYNTAX_ERROR);
				if (read_text(file->name, &(file->text)) != OK)
					return (MEMORY_ERROR);
			}
			file = file->next;
		}
		data = data->next;
	}
	return (OK);
}
