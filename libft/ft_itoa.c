/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:04:39 by stycho            #+#    #+#             */
/*   Updated: 2021/10/13 14:05:43 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned char	ft_get_len(int n);

char	*ft_itoa(int n)
{
	char			*char_repr;
	unsigned char	len;

	len = ft_get_len(n);
	char_repr = (char *)malloc(sizeof(char) * (len + 1));
	if (char_repr)
	{
		if (n == -2147483648)
			return (ft_memcpy(char_repr, "-2147483648", len + 1));
		char_repr[len] = '\0';
		if (n < 0)
		{
			char_repr[0] = '-';
			n *= -1;
		}
		while (n / 10 != 0)
		{
			char_repr[--len] = (n % 10) + '0';
			n /= 10;
		}
		char_repr[--len] = n + '0';
	}
	return (char_repr);
}

static unsigned char	ft_get_len(int n)
{
	unsigned char	len;

	len = 0;
	while (n / 10 != 0)
	{
		len++;
		n /= 10;
	}
	if (n < 0)
		len += 2;
	else
		len += 1;
	return (len);
}
