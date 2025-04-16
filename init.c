/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaterna <mmaterna@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:15:30 by mmaterna          #+#    #+#             */
/*   Updated: 2025/04/16 22:03:52 by mmaterna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

void	init_player(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	game->player.moves = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
			{
				game->player.pos.x = x;
				game->player.pos.y = y;
				return ;
			}
			x++;
		}
		y++;
	}
	game->player.pos.x = 1;
	game->player.pos.y = 1;
}

void	init_game_objects(t_game *game)
{
	int	y;
	int	x;

	game->collectibles = 0;
	game->collected = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'E')
			{
				game->exit_pos.x = x;
				game->exit_pos.y = y;
			}
			else if (game->map[y][x] == 'C')
			{
				game->collectibles++;
			}
			x++;
		}
		y++;
	}
}

int	initialize_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	return (1);
}

int	create_window_and_image(t_game *game)
{
	game->mlx_win = mlx_new_window(game->mlx, game->window_width,
			game->window_height, "so_long");
	if (!game->mlx_win)
		return (0);
	game->img.img = mlx_new_image(game->mlx, game->window_width, \
								game->window_height);
	if (!game->img.img)
		return (0);
	game->img.width = game->window_width;
	game->img.height = game->window_height;
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	return (1);
}

int	initialize_game(t_game *game)
{
	if (!initialize_mlx(game))
		return (0);
	if (!set_window_dimensions(game))
	{
		write(2, "Error: Invalid window dimensions\n", 34);
		return (0);
	}
	if (!create_window_and_image(game))
		return (0);
	if (!load_textures(game))
		return (0);
	init_player(game);
	init_game_objects(game);
	return (1);
}
