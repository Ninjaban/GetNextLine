/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 10:04:41 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/28 16:17:02 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 4096
# define DEL '\n'

# include <unistd.h>
# include <stdlib.h>

typedef struct	s_buf
{
	int			fd;
	char		*file;
	size_t		n;
}				t_buf;

int				get_next_line(int const fd, char **line);

#endif
