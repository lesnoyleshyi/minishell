/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 14:24:00 by stycho            #+#    #+#             */
/*   Updated: 2021/10/11 11:59:28 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*char_dst;
	char	*char_src;

	if (dst || src)
	{
		char_dst = (char *)dst;
		char_src = (char *)src;
		while (n--)
		{
			char_dst[n] = char_src[n];
		}
	}
	return (dst);
}
