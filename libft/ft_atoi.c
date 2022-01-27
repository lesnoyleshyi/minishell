/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 22:39:01 by stycho            #+#    #+#             */
/*   Updated: 2021/10/11 11:39:18 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int			minus_status;
	long long	res;

	res = 0;
	minus_status = 1;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus_status = -1;
		str++;
	}
	while (*str > 47 && *str < 58)
		res = (res * 10 + (*str++ - '0'));
	if (((unsigned long long)res > 9223372036854775807) && minus_status > 0)
		return (-1);
	if (((unsigned long long)res > 9223372036854775807) && minus_status < 0)
		return (0);
	return ((int)res * minus_status);
}
