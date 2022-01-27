/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 18:57:07 by stycho            #+#    #+#             */
/*   Updated: 2021/10/15 00:10:56 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char		*dst_pos;
	const char	*src_pos;
	size_t		dst_len;

	dst_pos = dst;
	src_pos = src;
	dst_len = 0;
	if (dstsize)
	{
		while (*dst_pos)
		{
			dst_pos++;
			dstsize--;
			if (dstsize == 0)
				return (ft_strlen(src) + (dst_pos - dst));
		}
		dst_len = dst_pos - dst;
		while (--dstsize && *src_pos)
			*dst_pos++ = *src_pos++;
		*dst_pos = '\0';
	}
	return ((dst_len) + ft_strlen(src));
}
