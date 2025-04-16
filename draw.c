/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaterna <mmaterna@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:40:24 by mmaterna          #+#    #+#             */
/*   Updated: 2025/04/16 15:43:40 by mmaterna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (!data->addr || x < 0 || y < 0 || x >= data->width || y >= data->height)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_texture(t_game *game, t_texture *texture, int x, int y)
{
	int				i;
	int				j;
	int				dest_x;
	int				dest_y;
	unsigned int	color;

	dest_y = 0;
	while (dest_y < game->tile_size && y + dest_y < game->img.height)
	{
		dest_x = 0;
		while (dest_x < game->tile_size && x + dest_x < game->img.width)
		{
			i = (int)(dest_y * texture->height / game->tile_size);
			j = (int)(dest_x * texture->width / game->tile_size);
			if (i < texture->height && j < texture->width)
			{
				color = *(unsigned int *)(texture->addr + \
				(i * texture->line_length + j * (texture->bits_per_pixel / 8)));
				if (color != 0xFF000000)
					my_mlx_pixel_put(&game->img, x + dest_x, y + dest_y, color);
			}
			dest_x++;
		}
		dest_y++;
	}
}

void	draw_tile(t_game *game, char tile_type, int x, int y)
{
	if (tile_type == '1')
		put_texture(game, &game->img.wall_texture, \
			x * game->tile_size, y * game->tile_size);
	else
		put_texture(game, &game->img.texture, \
			x * game->tile_size, y * game->tile_size);
	if (tile_type == 'C')
		put_texture(game, &game->collectible_texture, \
			x * game->tile_size, y * game->tile_size);
	else if (tile_type == 'E')
		put_texture(game, &game->exit_texture, \
			x * game->tile_size, y * game->tile_size);
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			draw_tile(game, game->map[y][x], x, y);
			x++;
		}
		y++;
	}
}
