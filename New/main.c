#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"

int		main(int ac, char **av)
{
  char	*line;
  int	fd;
  int	gnl_ret;

  fd = open(av[1], O_RDONLY);
  while ((gnl_ret = get_next_line(fd, &line)) == 1)
    printf("%d | %s\n", gnl_ret, line);
  printf("%d | %s\n", gnl_ret, line);

  return (0);
}
