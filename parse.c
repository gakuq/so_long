/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaterna <mmaterna@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:40:49 by mmaterna          #+#    #+#             */
/*   Updated: 2025/04/16 22:01:34 by mmaterna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

int	check_argument_format(int argc, char **argv, char \
						*map_path, size_t map_path_size)
{
	if (argc != 2)
	{
		write(2, "Usage: ./so_long <map_file.ber>\n", 32);
		return (0);
	}
	if (ft_strlcpy(map_path, "map/", map_path_size) >= map_path_size || \
		ft_strlcat(map_path, argv[1], map_path_size) >= map_path_size)
	{
		write(2, "Error: Map file path is too long\n", 33);
		return (0);
	}
	return (1);
}

int	parse_args_and_load_map(t_game *game, int argc, char **argv)
{
	char	map_path[256];

	if (!check_argument_format(argc, argv, map_path, sizeof(map_path)))
		return (0);
	game->map = load_map(map_path);
	if (!game->map)
		return (0);
	if (!validate_map(game))
	{
		free_map(game->map);
		return (0);
	}
	return (1);
}
