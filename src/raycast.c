/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 20:04:58 by pthorell          #+#    #+#             */
/*   Updated: 2018/09/05 14:14:39 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "raycast.h"
#include "draw.h"
#include "libft.h"
#include "texture_handler.h"
#include "color.h"
#include "keys.h"

#include <math.h>

#define POSX g->player.pos.x
#define POSY g->player.pos.y

static void	init_ray(t_ray *ray, t_game *g)
{
	ray->delta_dist.x = fabs(1 / ray->cos);
	ray->delta_dist.y = fabs(1 / ray->sin);
	ray->map_pos.x = (int)g->player.pos.x;
	ray->map_pos.y = (int)g->player.pos.y;
	if (ray->dir <= 90.0 || ray->dir >= 270.0)
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_pos.x - POSX + 1) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = -1;
		ray->side_dist.x = (POSX - ray->map_pos.x) * ray->delta_dist.x;
	}
	if (ray->dir >= 180.0)
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_pos.y - POSY + 1) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = -1;
		ray->side_dist.y = (POSY - ray->map_pos.y) * ray->delta_dist.y;
	}
}

static void	get_intersection(t_ray *ray, t_game *g)
{
	while (1)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_pos.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_pos.y += ray->step.y;
			ray->side = 1;
		}
		if (ray->map_pos.x > (g->map.w - 1) || ray->map_pos.x < 0)
			break ;
		if (ray->map_pos.y > (g->map.h - 1) || ray->map_pos.y < 0)
			break ;
		if (g->map.map[ray->map_pos.y][ray->map_pos.x] != '.')
			break ;
	}
}

#define LH ray->line.height

static void	put_line(t_ray *ray, t_game *g, int x)
{
	int	i;
	int	tex_x;
	int	tex_y;
	int	color;

	if (!ray->side)
		ray->wall_x = (g->player.pos.y + ray->wall_dist * -(ray->sin));
	else
		ray->wall_x = (g->player.pos.x + ray->wall_dist * ray->cos);
	ray->wall_x -= floor((ray->wall_x));
	tex_x = get_tex_x(ray);
	i = ray->line.start - 1;
	if (ray->wall_dist >= RENDER_DIST)
		return ;
	while (++i < ray->line.end)
	{
		tex_y = (64 * (LH - RES_Y + i * 2)) / (2 * LH);
		if (ray->texture == 8)
			color = get_demo_color(ray, g, tex_x, tex_y);
		else
			color = g->textures[ray->texture][TEXTURE_WIDTH * tex_y + tex_x];
		color = shade(color, RANGE(ray->wall_dist, 0.0, RENDER_DIST, 1.0, 0.0));
		put_pixel(x, i, color, g);
	}
}

#define WALLD ray->wall_dist
#define MAPC g->map.map[ray->map_pos.y][ray->map_pos.x]

static void	draw_ray(t_ray *ray, t_game *g, int x)
{
	if (ray->side == 0)
		WALLD = (ray->map_pos.x - POSX + (1 - ray->step.x) / 2) / ray->cos;
	else
		WALLD = -(ray->map_pos.y - POSY + (1 - ray->step.y) / 2) / ray->sin;
	ray->line.height = (int)(RES_Y / ray->wall_dist);
	ray->line.start = -(ray->line.height) / 2 + RES_Y / 2;
	if (ray->line.start < 0)
		ray->line.start = 0;
	ray->line.end = ray->line.height / 2 + RES_Y / 2;
	if (ray->line.end >= RES_Y)
		ray->line.end = RES_Y - 1;
	ray->texture = 0;
	if (ray->map_pos.x < g->map.w && ray->map_pos.y < g->map.h)
		if (ray->map_pos.x >= 0.0 && ray->map_pos.y >= 0.0)
			ray->texture = get_texture_number(MAPC);
	put_line(ray, g, x);
}

void		raycast(t_game *g)
{
	int		i;
	t_ray	ray;

	i = 0;
	while (i < RES_X)
	{
		ray.dir = (((i * FOV) / (double)RES_X) - FOV / 2.0) + g->player.rot;
		ray.dir = fmod(ray.dir, 360.0);
		if (ray.dir < 0)
			ray.dir += 360.0;
		ray.sin = sin(ray.dir * PI_OVER_180);
		ray.cos = cos(ray.dir * PI_OVER_180);
		init_ray(&ray, g);
		get_intersection(&ray, g);
		draw_ray(&ray, g, i);
		draw_floor(&ray, g, i);
		g->sprite_info.z_buff[i] = ray.wall_dist;
		draw_sprites(&ray, g, i);
		++i;
	}
	draw(g);
	clear(g);
}
