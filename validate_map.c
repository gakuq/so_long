/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaterna <mmaterna@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:09:15 by mmaterna          #+#    #+#             */
/*   Updated: 2025/04/16 22:17:35 by mmaterna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

int	check_map_characters(t_game *game, int *has_player, \
						int *has_exit, int *cols)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
				(*has_player)++;
			else if (game->map[y][x] == 'E')
				(*has_exit)++;
			else if (game->map[y][x] == 'C')
				(*cols)++;
			else if (game->map[y][x] != '0' && game->map[y][x] != '1')
				return (ft_putstr_fd(\
						"Error: Invalid character in map\n", 2), 0);
			x++;
		}
		y++;
	}
	return (1);
}

int	check_map_rectangle(t_game *game)
{
	int	y;
	int	first_len;

	first_len = ft_strlen(game->map[0]);
	y = 1;
	while (game->map[y])
	{
		if (ft_strlen(game->map[y]) != (size_t)first_len)
			return (ft_putstr_fd("Error: Map must be rectangular\n", 2), 0);
		y++;
	}
	return (1);
}

int	check_map_walls(t_game *game)
{
	int	y;
	int	x;
	int	width;
	int	height;

	height = 0;
	while (game->map[height])
		height++;
	width = ft_strlen(game->map[0]);
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if ((y == 0 || y == height - 1 || x == 0 || x == width - 1)
				&& game->map[y][x] != '1')
				return (ft_putstr_fd(\
					"Error: Map must be surrounded by walls\n", 2), 0);
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(t_game *game)
{
	int	has_player;
	int	has_exit;
	int	collectibles;

	has_player = 0;
	has_exit = 0;
	collectibles = 0;
	if (!check_map_rectangle(game))
		return (0);
	if (!check_map_characters(game, &has_player, &has_exit, &collectibles))
		return (0);
	if (!check_map_walls(game))
		return (0);
	if (has_player != 1 || has_exit != 1 || collectibles < 1)
		return (ft_putstr_fd("Error: Invalid number of elements\n", 2), 0);
	if (!check_path(game))
		return (0);
	return (1);
}

int	check_path(t_game *game)
{
	char	**map_copy;
	int		result;

	map_copy = copy_map(game->map);
	if (!map_copy)
		return (ft_putstr_fd("Error: Memory allocation failed\n", 2), 0);
	if (!find_player_and_flood(map_copy))
	{
		free_map_copy(map_copy);
		return (ft_putstr_fd("Error: Player position not found\n", 2), 0);
	}
	result = check_reachable_objects(map_copy);
	free_map_copy(map_copy);
	return (result);
}
