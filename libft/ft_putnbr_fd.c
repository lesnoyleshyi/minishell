/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:17:50 by stycho            #+#    #+#             */
/*   Updated: 2021/10/14 00:17:29 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_recursive_putnbr(int n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		write(fd, "-", sizeof(char));
	ft_recursive_putnbr(n, fd);
}

static void	ft_recursive_putnbr(int n, int fd)
{
	unsigned char	buf;

	if (n > 9 || n < -9)
	{
		ft_recursive_putnbr(n / 10, fd);
		buf = (n % 10) * ((n > 0) * 2 - 1) + '0';
		write(fd, &buf, sizeof(char));
		n /= 10;
	}
	else
	{
		buf = (n * ((n > 0) * 2 - 1)) + '0';
		write(fd, &buf, sizeof(char));
	}
}
