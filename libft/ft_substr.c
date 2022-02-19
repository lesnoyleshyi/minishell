/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:49:37 by stycho            #+#    #+#             */
/*   Updated: 2021/10/14 12:39:36 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	req_l;
	char	*s_pos;
	char	*s_copy;
	char	*s_copy_start;

	if (s)
	{
		s_pos = (char *)s;
		req_l = 0;
		s_copy_start = NULL;
		if (!((unsigned int)ft_strlen(s) <= start))
			while (*(s_pos++ + start) && len--)
				req_l++;
		s_copy = (char *)malloc((req_l + 1) * sizeof(char));
		if (s_copy)
		{
			s_copy_start = s_copy;
			while (req_l--)
				*s_copy++ = *(s++ + start);
			*s_copy = '\0';
		}
		return (s_copy_start);
	}
	return (NULL);
}
