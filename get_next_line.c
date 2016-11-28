/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 19:11:06 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/28 14:22:44 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/libft.h"
#include "get_next_line.h"

static int			ft_init_buf(t_buf ***buf)
{
	size_t			n;

	if (!(*buf))
	{
		if (((*buf) = malloc(sizeof(t_buf *) * 4096)) == NULL)
			return (-1);
		n = 0;
		while (n < 4096)
			(*buf)[n++] = NULL;
	}
	return (0);
}

static int			ft_ret_read(t_buf **buf, char **line)
{
	size_t			i;

	i = 0;
	(*line) = NULL;
	if ((*buf)->file[(*buf)->n] == '\0')
	{
		(*buf)->fd = -1;
		return (0);
	}
	if ((*line = malloc(ft_strlen((*buf)->file) + 1)) == NULL)
		return (-1);
	while ((*buf)->file[(*buf)->n] && (*buf)->file[(*buf)->n] != DEL)
		(*line)[i++] = (*buf)->file[(*buf)->n++];
	(*line)[i] = '\0';
	if ((*buf)->file[(*buf)->n] == DEL)
		(*buf)->n++;
	return (1);
}

static int			ft_complete_file(char **file, char *str, int ret)
{
	char			*tmp;

	str[ret] = '\0';
	if ((tmp = ft_strjoin(*file, str)) == NULL)
		return (-1);
	free(*file);
	*file = tmp;
	return (0);
}

static int			ft_read(t_buf ***buf, int fd, char **line)
{
	size_t			n;
	char			*tmp;
	int				ret;

	n = 0;
	while ((*buf)[n])
		n = n + 1;
	if ((tmp = malloc(BUFF_SIZE + 1)) == NULL)
		return (-1);
	if (((*buf)[n] = malloc(sizeof(t_buf))) == NULL)
		return (-1);
	(*buf)[n]->fd = fd;
	(*buf)[n]->n = 0;
	(*buf)[n]->file = ft_strdup("");
	while ((ret = read(fd, tmp, BUFF_SIZE)) == BUFF_SIZE)
		ft_complete_file(&((*buf)[n]->file), tmp, ret);
	if (ret == -1)
		return (-1);
	ft_complete_file(&((*buf)[n]->file), tmp, ret);
	free(tmp);
	return (ft_ret_read(&((*buf)[n]), &(*line)));
}

int					get_next_line(int const fd, char **line)
{
	static t_buf	**buf = NULL;
	size_t			n;

	n = 0;
	if (!line || fd == -1)
		return (-1);
	if (ft_init_buf(&buf) == -1)
		return (-1);
	while (buf[n] && buf[n]->fd != fd)
	{
		n = n + 1;
		if (buf[n] && buf[n]->file[buf[n]->n] == '\0')
			buf[n]->fd = -1;
	}
	if (n >= 4095)
		return (-1);
	if (buf[n] && buf[n]->fd == fd)
		return (ft_ret_read(&(buf[n]), &(*line)));
	else
		return (ft_read(&buf, fd, &(*line)));
}
