/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:01:03 by stycho            #+#    #+#             */
/*   Updated: 2021/10/13 18:16:03 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	s_len;
	char	*res_str;

	if (s)
	{
		s_len = ft_strlen(s);
		res_str = (char *)malloc((s_len + 1) * sizeof(char));
		if (res_str)
		{
			res_str[s_len] = '\0';
			while (s_len--)
				res_str[s_len] = (*f)(s_len, s[s_len]);
			return (res_str);
		}
	}
	return (NULL);
}
