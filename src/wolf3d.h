/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 01:33:20 by pthorell          #+#    #+#             */
/*   Updated: 2018/09/01 01:33:21 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <time.h>

# include "mlx.h"

# define RANGE(x, min, max, a, b) (((b - a) * (x - min)) / (max - min) + a)

# define RES_X 712
# define RES_Y 445

# define FOV 60

# define TEXTURE_COUNT 9
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define TEXTURE_TILES "WRreEpTD"

# define SPRITE_COUNT 10

# define RENDER_DIST 7

# define PI_OVER_180 0.01745329251
# define RAD_TO_DEG 57.2957795131

# define ENEMY_SPRITE 6
# define ENEMY_SPEED 0.025

# define PICKUP_SPRITE 7
# define PICKUP_COUNT 8
# define PICKUP_MSG_TIME 5

# define EXIT_SPRITE 8

# define COLLIDE_RANGE 0.2

typedef struct	s_2d
{
	double		x;
	double		y;
}				t_2d;

typedef struct	s_win
{
	void		*mlx;
	void		*window;
}				t_win;

typedef struct	s_image
{
	void		*image;
	char		*img_data;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_image;

typedef struct	s_map
{
	char		**map;
	short		w;
	short		h;
}				t_map;

typedef struct	s_player
{
	t_2d		pos;
	int			score;
	double		rot;
}				t_player;

typedef struct	s_sprinf
{
	int			sprite_order[SPRITE_COUNT];
	double		z_buff[RES_X];
	double		sprite_distance[SPRITE_COUNT];
}				t_sprinf;

typedef struct	s_sprite
{
	t_2d		pos;
	int			texture;
	double		size;
}				t_sprite;

typedef struct	s_game
{
	t_win		window;
	t_player	player;
	t_map		map;
	t_image		image;
	t_sprinf	sprite_info;
	t_sprite	sprites[SPRITE_COUNT];
	int			keys[512];
	int			textures[TEXTURE_COUNT][TEXTURE_HEIGHT * TEXTURE_WIDTH];
}				t_game;

#endif
