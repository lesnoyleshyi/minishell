/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:49:00 by stycho            #+#    #+#             */
/*   Updated: 2021/10/11 12:00:11 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*char_dst;
	const char	*char_src;

	if (src || dst)
	{
		char_dst = (char *)dst;
		char_src = (char *)src;
		if (char_dst < char_src)
			while (len--)
				*char_dst++ = *char_src++;
		else
			while (len--)
				*(char_dst + len) = *(char_src + len);
	}
	return (dst);
}
