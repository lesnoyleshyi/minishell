/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:49:48 by stycho            #+#    #+#             */
/*   Updated: 2021/10/11 13:49:50 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

char	*ft_strdup(const char *s1)
{
	char	*p_to_copy;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	p_to_copy = (char *)malloc((s1_len + 1) * sizeof(char));
	if (p_to_copy)
	{
		ft_strlcpy(p_to_copy, s1, s1_len + 1);
	}
	return (p_to_copy);
}
