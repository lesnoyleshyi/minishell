
#include "stdlib.h"
#include "unistd.h"
#include "printf.h"
#include "fcntl.h"

int	main(void) {
	int		fd;
	char	buf;
	char	*pathname = "Makefile";

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		printf("I can't open it\n");
		exit(1);
	}
	while (read(fd, &buf, 1) > 0)
		write(1, &buf, 1);
	return (0);
}