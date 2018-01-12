//
// Created by Nathan on 11/01/18.
//

#include <stdlib.h>
#include "get_next_line.h"
#include "libft.h"

void	ft_read_stock(char **buf, char read_buf[BUFF_SIZE + 1], int read_ret)
{
	char		*buf_tmp;

	read_buf[read_ret] = '\0';
	buf_tmp = (!(*buf)) ? ft_strdup(read_buf) : ft_strjoin(*buf, read_buf);
	free(*buf);
	*buf = buf_tmp;

}

int		ft_read(const int fd, char **buf)
{
	char		read_buf[BUFF_SIZE + 1];
	int			read_ret;

	if ((read_ret = (int)read(fd, read_buf, BUFF_SIZE)) == -1)
		return (-1);
	if (read_ret)
	{
		ft_read_stock(buf, read_buf, read_ret);
		return (1);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char	*buf = NULL;
	char		*strchr_ret;
	char		c;
	int			ft_read_ret;

	if (!line || fd < 0 || BUFF_SIZE <= 0)
		return (-1);
	ft_read_ret = 1;
	while (ft_read_ret == 1)
	{
		if ((ft_read_ret = ft_read(fd, &buf)) == -1)
			return (-1);
		if (buf && ((strchr_ret = ft_strchr(buf, '\n')) || ft_read_ret == 0))
		{
			if (ft_read_ret == 0 && !strchr_ret)
				strchr_ret = buf + ft_strlen(buf);
			c = strchr_ret[0];
			strchr_ret[0] = '\0';
			*line = ft_strdup(buf);
			buf = ft_strcpy(buf, (c == '\n') ? strchr_ret + 1 : strchr_ret);
			if (!ft_strlen(buf))
				ft_strdel(&buf);
			return (1);
		}
	}
	*line = NULL;
	return (0);
}