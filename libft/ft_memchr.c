/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:20:15 by stycho            #+#    #+#             */
/*   Updated: 2021/10/08 15:20:56 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*ch_s;

	ch_s = s;
	while (n--)
	{
		if (*ch_s == (char)c)
			return ((void *)ch_s);
		ch_s++;
	}
	return (NULL);
}
