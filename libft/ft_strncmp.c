/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 21:24:18 by stycho            #+#    #+#             */
/*   Updated: 2021/10/10 10:39:40 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		delta;

	i = 0;
	while (n--)
	{
		delta = (unsigned char)s1[i] - s2[i];
		if (delta != 0 || s1[i] == '\0' || s2[i] == '\0')
			return (delta);
		i++;
	}
	return (0);
}
