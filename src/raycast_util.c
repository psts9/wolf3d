/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 21:32:40 by pthorell          #+#    #+#             */
/*   Updated: 2018/08/31 21:33:13 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "raycast.h"

#include <math.h>

#define POSX g->player.pos.x
#define POSY g->player.pos.y

int	get_tex_x(t_ray *ray)
{
	int result;

	result = (int)(ray->wall_x * (double)TEXTURE_WIDTH);
	if (!ray->side && (ray->dir > 270 || ray->dir < 90))
		result = (TEXTURE_WIDTH - result - 1);
	if (ray->side && ray->dir < 180)
		result = (TEXTURE_WIDTH - result - 1);
	return (result);
}

int	get_demo_color(t_ray *ray, t_game *g, int tex_x, int tex_y)
{
	int		text;
	double	rel_ang;

	rel_ang = atan2(ray->map_pos.x - POSX, ray->map_pos.y - POSY) * RAD_TO_DEG;
	if (rel_ang < 0 && rel_ang > -90)
		text = (ray->side ? 4 : 5);
	else if (rel_ang > 0 && rel_ang < 90)
		text = (ray->side ? 4 : 6);
	else if (rel_ang > 90)
		text = (ray->side ? 7 : 6);
	else
		text = (ray->side ? 7 : 5);
	return (g->textures[text][TEXTURE_WIDTH * tex_y + tex_x]);
}
