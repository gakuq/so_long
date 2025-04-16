/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaterna <mmaterna@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:37:58 by mmaterna          #+#    #+#             */
/*   Updated: 2025/04/16 21:51:46 by mmaterna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include "../Libft/libft.h"
# include "../gnl/get_next_line.h"
# include <fcntl.h>
# include <unistd.h>

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363

typedef struct s_txt
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_texture;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_player
{
	t_pos		pos;
	t_texture	texture;
	int			moves;
}	t_player;

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	t_texture	texture;
	t_texture	wall_texture;
}	t_data;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	char		**map;
	int			window_width;
	int			window_height;
	int			tile_size;
	t_player	player;
	int			collectibles;
	int			collected;
	t_texture	collectible_texture;
	t_texture	exit_texture;
	t_pos		exit_pos;
}	t_game;

// Funkcje obsługi gracza
int		key_handler(int keycode, t_game *game);
void	init_player(t_game *game);
void	draw_player(t_game *game);
void	move_player(t_game *game, int dx, int dy);

// Funkcje obsługi grafiki
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	put_texture(t_game *game, t_texture *texture, int x, int y);
void	draw_map(t_game *game);
int		update_display(t_game *game);

// Funkcje obsługi mapy
char	**load_map(const char *file_path);
void	init_game_objects(t_game *game);

// Funkcje inicjalizacji i wczytywania
int		initialize_mlx(t_game *game);
int		set_window_dimensions(t_game *game);
int		create_window_and_image(t_game *game);
int		initialize_game(t_game *game);
int		load_textures(t_game *game);
int		load_floor_texture(t_game *game);
int		load_wall_texture(t_game *game);
int		load_player_texture(t_game *game);
int		load_collectible_texture(t_game *game);
int		load_exit_texture(t_game *game);
int		parse_args_and_load_map(t_game *game, int argc, char **argv);

// Funkcje walidacji mapy
int		validate_map(t_game *game);
int		check_map_characters(t_game *game, int *has_player, \
							int *has_exit, int *cols);
int		check_map_rectangle(t_game *game);
int		check_map_walls(t_game *game);
int		check_path(t_game *game);
void	flood_fill(char **map_copy, int x, int y);
char	**copy_map(char **map);
void	free_map_copy(char **map_copy);
int		find_player_and_flood(char **map_copy);
int		check_reachable_objects(char **map_copy);

// Funkcje pomocnicze do zarządzania mapą
char	**allocate_map(void);
char	**process_map_lines(int fd, char **map);
void	draw_tile(t_game *game, char tile_type, int x, int y);
void	free_map(char **map);
int		check_argument_format(int argc, char **argv, \
							char *map_path, size_t map_path_size);

#endif