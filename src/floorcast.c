/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 17:41:41 by pthorell          #+#    #+#             */
/*   Updated: 2018/08/31 18:59:15 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "raycast.h"
#include "draw.h"
#include "libft.h"
#include "texture_handler.h"
#include "color.h"

#include <math.h>

#define GPOSX g->player.pos.x
#define GPOSY g->player.pos.y
#define FLTEX g->textures[3][TEXTURE_WIDTH * floor_tex.y + floor_tex.x]
#define RFTEX g->textures[2][TEXTURE_WIDTH * floor_tex.y + floor_tex.x]
#define FLSHA (RENDER_DIST / 1.8)

static t_2d	get_floor_wall(t_ray *ray)
{
	t_2d result;

	if (ray->side == 0 && (ray->dir >= 270.0 || ray->dir <= 90.0))
	{
		result.x = ray->map_pos.x;
		result.y = ray->map_pos.y + ray->wall_x;
	}
	else if (ray->side == 0)
	{
		result.x = ray->map_pos.x + 1.0;
		result.y = ray->map_pos.y + ray->wall_x;
	}
	else if (ray->side == 1 && ray->dir >= 180.0)
	{
		result.x = ray->map_pos.x + ray->wall_x;
		result.y = ray->map_pos.y;
	}
	else
	{
		result.x = ray->map_pos.x + ray->wall_x;
		result.y = ray->map_pos.y + 1.0;
	}
	return (result);
}

void		draw_floor(t_ray *ray, t_game *g, int x)
{
	int		y;
	t_2d	floor_wall;
	t_2d	current_floor;
	double	weight;
	t_point	floor_tex;

	floor_wall = get_floor_wall(ray);
	if (ray->line.end < 0)
		ray->line.end = RES_Y;
	y = ray->line.end + 1;
	while (y < RES_Y)
	{
		if ((RES_Y - y) / 2 >= 255)
			break ;
		weight = (RES_Y / (2.0 * y - RES_Y)) / ray->wall_dist;
		current_floor.x = weight * floor_wall.x + (1.0 - weight) * GPOSX;
		current_floor.y = weight * floor_wall.y + (1.0 - weight) * GPOSY;
		floor_tex.x = (int)(current_floor.x * TEXTURE_WIDTH) % TEXTURE_WIDTH;
		floor_tex.y = (int)(current_floor.y * TEXTURE_HEIGHT) % TEXTURE_HEIGHT;
		put_pixel(x, y, sub_color(FLTEX, (RES_Y - y + 1) / FLSHA), g);
		put_pixel(x, RES_Y - y, sub_color(RFTEX, (RES_Y - y + 1) / FLSHA), g);
		++y;
	}
}
