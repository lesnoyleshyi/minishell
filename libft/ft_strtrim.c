/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 23:11:03 by stycho            #+#    #+#             */
/*   Updated: 2021/10/14 23:38:33 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	req_len;

	if (s1)
	{
		req_len = 0;
		while (*s1 && ft_strchr(set, *s1))
			s1++;
		while (*s1)
		{
			s1++;
			req_len++;
		}
		while (req_len && ft_strchr(set, *(--s1)))
			req_len--;
		if (req_len == 0)
			return (ft_strdup(""));
		res = (char *)malloc((req_len + 1) * sizeof(char));
		if (res)
			ft_strlcpy(res, s1 - req_len + 1, req_len + 1);
		return (res);
	}
	return (NULL);
}
