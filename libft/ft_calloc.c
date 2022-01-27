/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:14:13 by stycho            #+#    #+#             */
/*   Updated: 2021/10/13 21:25:17 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t count, size_t size)
{
	size_t	*p;

	p = (size_t *)malloc(count * size * sizeof(char));
	if (!(p))
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}
