/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaterna <mmaterna@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:26:28 by mmaterna          #+#    #+#             */
/*   Updated: 2025/04/16 15:37:12 by mmaterna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

int	load_floor_texture(t_game *game)
{
	game->img.texture.img = mlx_xpm_file_to_image(game->mlx, "img/stone.xpm",
			&game->img.texture.width, &game->img.texture.height);
	if (!game->img.texture.img)
	{
		write(2, "Error: Failed to load floor texture\n", 36);
		return (0);
	}
	game->img.texture.addr = mlx_get_data_addr(game->img.texture.img,
			&game->img.texture.bits_per_pixel, &game->img.texture.line_length,
			&game->img.texture.endian);
	return (1);
}

int	load_wall_texture(t_game *game)
{
	game->img.wall_texture.img = mlx_xpm_file_to_image(game->mlx, \
						"img/wall.xpm", &game->img.wall_texture.width, \
						&game->img.wall_texture.height);
	if (!game->img.wall_texture.img)
	{
		write(2, "Error: Failed to load wall texture\n", 35);
		return (0);
	}
	game->img.wall_texture.addr = mlx_get_data_addr(game->img.wall_texture.img, \
			&game->img.wall_texture.bits_per_pixel, \
			&game->img.wall_texture.line_length, \
			&game->img.wall_texture.endian);
	return (1);
}

int	load_player_texture(t_game *game)
{
	game->player.texture.img = mlx_xpm_file_to_image(game->mlx, \
					"img/player.xpm", &game->player.texture.width, \
					&game->player.texture.height);
	if (!game->player.texture.img)
	{
		write(2, "Error: Failed to load player texture\n", 37);
		return (0);
	}
	game->player.texture.addr = mlx_get_data_addr(game->player.texture.img, \
										&game->player.texture.bits_per_pixel, \
										&game->player.texture.line_length, \
										&game->player.texture.endian);
	return (1);
}

int	load_collectible_texture(t_game *game)
{
	game->collectible_texture.img = mlx_xpm_file_to_image(game->mlx,
			"img/coin.xpm", &game->collectible_texture.width,
			&game->collectible_texture.height);
	if (!game->collectible_texture.img)
	{
		write(2, "Error: Failed to load collectible texture\n", 42);
		return (0);
	}
	game->collectible_texture.addr = mlx_get_data_addr(\
									game->collectible_texture.img, \
									&game->collectible_texture.bits_per_pixel, \
									&game->collectible_texture.line_length, \
									&game->collectible_texture.endian);
	return (1);
}

int	load_exit_texture(t_game *game)
{
	game->exit_texture.img = mlx_xpm_file_to_image(game->mlx, \
					"img/exit.xpm", &game->exit_texture.width, \
					&game->exit_texture.height);
	if (!game->exit_texture.img)
	{
		write(2, "Error: Failed to load exit texture\n", 35);
		return (0);
	}
	game->exit_texture.addr = mlx_get_data_addr(game->exit_texture.img,
			&game->exit_texture.bits_per_pixel,
			&game->exit_texture.line_length, &game->exit_texture.endian);
	return (1);
}
