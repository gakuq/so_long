/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaterna <mmaterna@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:38:06 by mmaterna          #+#    #+#             */
/*   Updated: 2025/04/16 21:41:56 by mmaterna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

int	key_handler(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(game->mlx, game->mlx_win);
		exit(0);
	}
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_player(game, 1, 0);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move_player(game, -1, 0);
	else if (keycode == KEY_W || keycode == KEY_UP)
		move_player(game, 0, -1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_player(game, 0, 1);
	return (0);
}

int	set_window_dimensions(t_game *game)
{
	int		map_height;
	int		map_width;
	int		max_width;
	int		max_height;
	float	scale;

	max_width = 1920;
	max_height = 1080;
	game->tile_size = 64;
	map_height = 0;
	while (game->map[map_height])
		map_height++;
	map_width = ft_strlen(game->map[0]);
	game->window_width = game->tile_size * map_width;
	game->window_height = game->tile_size * map_height;
	if (game->window_width > max_width || game->window_height > max_height)
	{
		scale = (float)max_width / game->window_width;
		if ((float)max_height / game->window_height < scale)
			scale = (float)max_height / game->window_height;
		game->tile_size = (int)(game->tile_size * scale);
		game->window_width = game->tile_size * map_width;
		game->window_height = game->tile_size * map_height;
	}
	return (game->window_width > 0 && game->window_height > 0);
}

int	load_textures(t_game *game)
{
	if (!load_floor_texture(game) || !load_wall_texture(game) || \
		!load_player_texture(game) || !load_collectible_texture(game) || \
		!load_exit_texture(game))
		return (0);
	return (1);
}

// Funkcja do aktualizacji ekranu po ruchu
int	update_display(t_game *game)
{
	char	info_str[100];

	mlx_clear_window(game->mlx, game->mlx_win);
	draw_map(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
	snprintf(info_str, sizeof(info_str), "Moves: %d | Collected: %d/%d", \
		game->player.moves, game->collected, game->collectibles);
	mlx_string_put(game->mlx, game->mlx_win, 10, 20, 0xFFFFFF, info_str);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!parse_args_and_load_map(&game, argc, argv))
		return (1);
	if (!initialize_game(&game))
		return (1);
	update_display(&game);
	mlx_key_hook(game.mlx_win, key_handler, &game);
	mlx_loop(game.mlx);
	return (0);
}
