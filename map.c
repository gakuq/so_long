/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaterna <mmaterna@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:06:04 by mmaterna          #+#    #+#             */
/*   Updated: 2025/04/16 22:14:06 by mmaterna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

char	**allocate_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 101);
	if (!map)
		return (NULL);
	return (map);
}

char	**process_map_lines(int fd, char **map)
{
	char	*line;
	int		i;
	size_t	len;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		map[i++] = line;
		if (i >= 100)
			break ;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	if (i == 0)
	{
		write(2, "Error: Map is empty\n", 20);
		free(map);
		return (NULL);
	}
	return (map);
}

char	**load_map(const char *file_path)
{
	int		fd;
	char	**map;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error: failed to open map\n", 27);
		return (NULL);
	}
	map = allocate_map();
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	map = process_map_lines(fd, map);
	close(fd);
	return (map);
}
