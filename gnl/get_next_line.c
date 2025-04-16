/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaterna <mmaterna@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 08:38:53 by mmaterna          #+#    #+#             */
/*   Updated: 2025/02/06 09:37:19 by mmaterna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*buf;
	char		*line;
	int			r;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	r = 1;
	while ((!saved || !ft_strchr(saved, '\n')) && r > 0)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r <= 0)
			break ;
		buf[r] = '\0';
		saved = str_join(saved, buf);
	}
	free(buf);
	if (r < 0 || !saved)
		return (NULL);
	line = get_line(saved);
	saved = save_remaining(saved);
	return (line);
}
