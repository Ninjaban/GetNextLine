/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 19:11:06 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/18 21:06:09 by jcarra           ###   ########.fr       */
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

static int			ft_find_fd(t_buf **buf, int fd)
{
	size_t			n;

	n = 0;
	while (buf[n])
		if (buf[n++]->fd == fd)
			return (n - 1);
	return (-1);
}

static int			ft_ret_read(t_buf **buf, char **line)
{
	size_t			n;

	n = 0;
	if ((*buf)->file[(*buf)->n] == '\0')
		return (0);
	if ((*line = malloc(ft_strlen((*buf)->file) + 1)) == NULL)
		return (-1);
	while ((*buf)->file[(*buf)->n] && (*buf)->file[(*buf)->n] != DEL)
		(*line)[n++] = (*buf)->file[(*buf)->n++];
	(*line)[n] = '\0';
	if ((*buf)->file[(*buf)->n] == DEL)
		(*buf)->n++;
	if ((*buf)->file[(*buf)->n] == '\0')
		return (0);
	return (1);
}

static int			ft_complete_file(char **file, char *str, int ret)
{
	char			*tmp;

	str[ret] = '\0';
	tmp = ft_strjoin(*file, str);
	free(*file);
	*file = tmp;
}

static int			ft_read(t_buf ***buf, int fd, char **line)
{
	size_t			n;
	char			*tmp;
	int				ret;

	n = 0;
	while ((*buf)[n])
		n = n + 1;
	if ((tmp = malloc(BUFFER_SIZE)) == NULL)
		return (-1);
	if (((*buf)[n] = malloc(sizeof(t_buf))) == NULL)
		return (-1);
	(*buf)[n]->fd = fd;
	(*buf)[n]->n = 0;
	(*buf)[n]->file = ft_strdup("");
	while ((ret = read(fd, tmp, BUFFER_SIZE)) == BUFFER_SIZE)
		ft_complete_file(&((*buf)[n]->file), tmp, ret);
	ft_complete_file(&((*buf)[n]->file), tmp, ret);
	free(tmp);
	return (ft_ret_read(&((*buf)[n]), &(*line)));
}

int					get_next_line(int const fd, char **line)
{
	static t_buf	**buf = NULL;
	size_t			n;

	n = 0;
	if (!line)
		return (-1);
	if (ft_init_buf(&buf) == -1)
		return (-1);
	if ((n = ft_find_fd(buf, fd)) != -1)
		return (ft_ret_read(&(buf[n]), &(*line)));
	else
		return (ft_read(&buf, fd, &(*line)));
}
