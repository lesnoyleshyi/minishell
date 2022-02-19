/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:54:01 by stycho            #+#    #+#             */
/*   Updated: 2021/10/12 20:01:12 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ch_s1;
	unsigned char	*ch_s2;

	ch_s1 = (unsigned char *)s1;
	ch_s2 = (unsigned char *)s2;
	while (n--)
	{
		if (*ch_s1 != *ch_s2)
			return (*ch_s1 - *ch_s2);
		ch_s1++;
		ch_s2++;
	}
	return (0);
}
