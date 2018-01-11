//
// Created by Nathan on 11/01/18.
//

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"

int		ft_read(const int fd, char **buf)
{
	char		read_buf[BUFF_SIZE + 1];
	char		*buf_tmp;
	int			read_ret;

	while ((read_ret = (int)read(fd, read_buf, BUFF_SIZE)) > 0)
	{
		read_buf[read_ret] = '\0';
		buf_tmp = (!(*buf)) ? ft_strdup(read_buf) : ft_strjoin(*buf, read_buf);
		free(*buf);
		*buf = buf_tmp;
	}
	if (read_ret == -1)
		return (-1);
	if (read_ret)
	{
		read_buf[read_ret] = '\0';
		buf_tmp = (!(*buf)) ? ft_strdup(read_buf) : ft_strjoin(*buf, read_buf);
		free(*buf);
		*buf = buf_tmp;
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char	*buf = NULL;
	char		*strchr_ret;

	if (!line || fd < 0)
		return (-1);
	if (!buf && ft_read(fd, &buf) == -1)
		return (-1);
	if (buf)
	{
		if (!(strchr_ret = ft_strchr(buf, '\n')))
			strchr_ret = buf + ft_strlen(buf);
		strchr_ret[0] = '\0';
		*line = ft_strdup(buf);
		buf = ft_strcpy(buf, strchr_ret + 1);
		if (!ft_strlen(buf))
			ft_strdel(&buf);
		return (1);
	}
	*line = NULL;
	return (0);
}