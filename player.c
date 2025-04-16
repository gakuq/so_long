/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaterna <mmaterna@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:16:49 by mmaterna          #+#    #+#             */
/*   Updated: 2025/04/16 21:54:57 by mmaterna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

void	handle_collectible(t_game *game, int new_x, int new_y)
{
	game->collected++;
	game->map[new_y][new_x] = '0';
}

void	handle_exit(t_game *game)
{
	if (game->collected == game->collectibles)
	{
		mlx_destroy_window(game->mlx, game->mlx_win);
		ft_printf("Congratulations! You completed the level in %d moves.\n",
			game->player.moves + 1);
		exit(0);
	}
	else
	{
		ft_printf("You need to collect all %d coins first! (%d/%d collected)\n",
			game->collectibles, game->collected, game->collectibles);
	}
}

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player.pos.x + dx;
	new_y = game->player.pos.y + dy;
	if (game->map[new_y][new_x] == '1')
		return ;
	if (game->map[new_y][new_x] == 'C')
		handle_collectible(game, new_x, new_y);
	if (game->map[new_y][new_x] == 'E')
	{
		handle_exit(game);
		return ;
	}
	game->player.pos.x = new_x;
	game->player.pos.y = new_y;
	game->player.moves++;
	update_display(game);
}

void	draw_player(t_game *game)
{
	put_texture(game, &game->player.texture,
		game->player.pos.x * game->tile_size,
		game->player.pos.y * game->tile_size);
}
