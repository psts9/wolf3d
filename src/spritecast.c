/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 00:27:15 by pthorell          #+#    #+#             */
/*   Updated: 2018/09/05 14:28:48 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "raycast.h"
#include "draw.h"
#include "libft.h"
#include "texture_handler.h"
#include "color.h"
#include "sprites.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SSZ g->sprites[g->sprite_info.sprite_order[i]].size

static t_spritecast	get_screen_pos(t_game *g, int i)
{
	t_spritecast	sprite;
	t_2d			inc;

	inc.x = g->sprites[g->sprite_info.sprite_order[i]].pos.x - g->player.pos.x;
	inc.y = g->sprites[g->sprite_info.sprite_order[i]].pos.y - g->player.pos.y;
	sprite.dist = sqrt(inc.x * inc.x + inc.y * inc.y);
	sprite.tex_floor = TEXTURE_HEIGHT / sprite.dist * (1 / SSZ);
	sprite.dir = g->player.rot + atan2(inc.y, inc.x) * RAD_TO_DEG;
	if (sprite.dir > 180.0)
		sprite.dir -= 360.0;
	sprite.screen_x = RANGE(sprite.dir, -FOV / 2, FOV / 2, RES_X, 0);
	sprite.height = RES_Y / sprite.dist * SSZ;
	sprite.draw_start_x = sprite.screen_x - sprite.height / 2;
	if (sprite.draw_start_x < 0)
		sprite.draw_start_x = 0;
	sprite.draw_end_x = sprite.screen_x + sprite.height / 2;
	if (sprite.draw_end_x >= RES_X)
		sprite.draw_end_x = RES_X - 1;
	sprite.draw_start_y = RES_Y / 2 - sprite.height / 2 + sprite.tex_floor;
	if (sprite.draw_start_y < 0)
		sprite.draw_start_y = 0;
	sprite.draw_end_y = RES_Y / 2 + sprite.height / 2 + sprite.tex_floor;
	if (sprite.draw_end_y >= RES_Y)
		sprite.draw_end_y = RES_Y - 1;
	return (sprite);
}

#define WD g->sprite_info.z_buff[x]
#define SX (x - (-sprite->height / 2 + sprite->screen_x))
#define CS g->sprites[g->sprite_info.sprite_order[i]].texture
#define SH sprite->height
#define SD sprite->dist

static int			fix_texnum(int n)
{
	if (n < 0)
		return (0);
	else if (n >= TEXTURE_WIDTH)
		return (TEXTURE_WIDTH - 1);
	else
		return (n);
}

#define SF sprite->tex_floor
#define TH TEXTURE_HEIGHT

static void			render_sprite(t_spritecast *sprite, t_game *g, int i, int x)
{
	int y;
	int tex_x;
	int tex_y;
	int color;

	if (x >= sprite->draw_start_x && x <= sprite->draw_end_x)
	{
		if (sprite->dist < WD && sprite->dist < RENDER_DIST)
		{
			tex_x = (int)((SX * TEXTURE_WIDTH) / sprite->height);
			tex_x = fix_texnum(tex_x);
			y = sprite->draw_start_y - 1;
			while (++y < sprite->draw_end_y)
			{
				tex_y = (TH * (-2 * SF + SH + 2 * y - RES_Y)) / (2 * SH);
				tex_y = fix_texnum(tex_y);
				color = g->textures[CS][TEXTURE_WIDTH * tex_y + tex_x];
				if (color != 16777215)
				{
					color = shade(color, RANGE(SD, 0.0, RENDER_DIST, 1.0, 0.0));
					put_pixel(x, y, color, g);
				}
			}
		}
	}
}

static double		get_sprite_dist(t_game *g, int i)
{
	double	tmp1;
	double	tmp2;

	tmp1 = g->player.pos.x - g->sprites[i].pos.x;
	tmp2 = g->player.pos.y - g->sprites[i].pos.y;
	return (tmp1 * tmp1 + tmp2 * tmp2);
}

void				draw_sprites(t_ray *ray, t_game *g, int x)
{
	int				i;
	t_spritecast	sprite;

	i = 0;
	while (i < SPRITE_COUNT)
	{
		g->sprite_info.sprite_order[i] = i;
		g->sprite_info.sprite_distance[i] = get_sprite_dist(g, i);
		++i;
	}
	sort_sprites(g);
	i = 0;
	while (i < SPRITE_COUNT)
	{
		sprite = get_screen_pos(g, i);
		render_sprite(&sprite, g, i, x);
		++i;
	}
	ray->cos += 0.0;
	x += 0.0;
}
