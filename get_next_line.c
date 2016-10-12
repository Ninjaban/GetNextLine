#include "get_next_line.h"

int	ft_end(int ret, int size)
{
  if (ret == -1)
    return (-1);
  if (ret == 0 && size > 0)
    return (1);
  if (ret == 0 && size == 0)
    return (0);
  return (0);
}

int	get_next_line(int cont fd, char **line)
{
  int	ret;
  int	size;
  char	c;

  size = 0;
  while (size < BUFFER_SIZE)
    {
      if ((ret = read(fd, &c, 1)) > 0)
	{
	  if (c == '\n')
	    {
	      *(line)[size] = '\0';
	      return (1);
	    }
	  *(line)[size++] = c;
	}
      else
	return (ft_end(ret, size));
      size = size + 1;
    }
  return (0);
}
