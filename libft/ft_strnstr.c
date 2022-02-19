/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 20:53:14 by stycho            #+#    #+#             */
/*   Updated: 2021/10/15 12:17:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	ndl_len;

	if (!(*needle))
		return ((char *)haystack);
	ndl_len = ft_strlen(needle);
	while (len && *(haystack + ndl_len - 1) && *haystack)
	{
		if (ndl_len <= len)
			if ((ft_strncmp(haystack, needle, ndl_len) == 0))
				return ((char *)haystack);
		len--;
		haystack++;
	}
	return (NULL);
}
