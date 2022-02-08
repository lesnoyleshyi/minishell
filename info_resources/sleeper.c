
#include "stdio.h"
#include "../libft/libft.h"

int	main(int argc, char *argv[])
{
	int		sleep_seconds;
	int		i;
	char	buf;

	if (argc != 2)
	{
		write(2, "Provide amount of seconds to sleep as an argument\n", 51);
		return (1);
	}
	while (read(0, &buf, 1) == 1)
		write(1, &buf, 1);
	sleep_seconds = ft_atoi(argv[1]);
	printf("hello! I'll sleep %d seconds\n", sleep_seconds);
	i = 0;
	while (i++ < sleep_seconds)
	{
		sleep(1);
		printf("I've slept %d of %d seconds\n", i, sleep_seconds);
	}
	return (0);
}