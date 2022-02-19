/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 22:02:33 by stycho            #+#    #+#             */
/*   Updated: 2021/10/15 22:02:34 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(const char *raw_str, char sp);
static char		*ft_all_mem_for_word(const char *p_to_raw_str, char term_symb);
static void		ft_copy_word(char *dst, const char *src, char term_symb);
static char		**ft_check_leaks(char **arr_of_strings, size_t i);

char	**ft_split(char	const *s, char c)
{
	size_t	word_count;
	size_t	i;
	char	**splitted_words;
	char	*word;

	if (!(s))
		return (NULL);
	word_count = ft_count_words(s, c);
	splitted_words = (char **)ft_calloc((word_count + 1), sizeof(char *));
	i = 0;
	while (*s && i < word_count)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		word = ft_all_mem_for_word(s, c);
		if (!(word))
			return (ft_check_leaks(splitted_words, i));
		splitted_words[i++] = word;
		ft_copy_word(word, s, c);
		while (*s && *s != c)
			s++;
	}
	return (splitted_words);
}

static size_t	ft_count_words(const char *raw_str, char sp)
{
	size_t	count;

	count = 0;
	while (*raw_str)
	{
		if (*raw_str == sp)
			raw_str++;
		else
		{
			count++;
			while (*raw_str != sp && *raw_str != '\0')
				raw_str++;
		}
	}
	return (count);
}

static char	*ft_all_mem_for_word(const char *p_to_raw_str, char term_symb)
{
	char		*p_to_blank_word;
	const char	*copy_ptrawstr;
	size_t		w_len;

	copy_ptrawstr = p_to_raw_str;
	w_len = 0;
	while (*copy_ptrawstr && *copy_ptrawstr != term_symb)
	{
		w_len++;
		copy_ptrawstr++;
	}
	p_to_blank_word = (char *)ft_calloc((w_len + 1), sizeof(char));
	return (p_to_blank_word);
}

static void	ft_copy_word(char *dst, const char *src, char term_symb)
{
	char	*copy_src;

	copy_src = (char *)src;
	while (*copy_src && *copy_src != term_symb)
		*(dst++) = *(copy_src++);
}

static char	**ft_check_leaks(char **arr_of_strings, size_t i)
{
	while (i--)
		free(arr_of_strings[i]);
	free(arr_of_strings);
	return (NULL);
}
