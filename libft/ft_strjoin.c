/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:46:13 by stycho            #+#    #+#             */
/*   Updated: 2021/10/14 12:51:39 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*res;
	char	*res_start;

	if (s1 && s2)
	{
		len_s1 = ft_strlen(s1);
		len_s2 = ft_strlen(s2);
		res = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
		if (res)
		{
			res_start = res;
			while (len_s1--)
				*res++ = *s1++;
			while (len_s2--)
				*res++ = *s2++;
			*res = '\0';
			return (res_start);
		}
		return (res);
	}
	return (NULL);
}
