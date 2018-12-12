/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 21:31:26 by pthorell          #+#    #+#             */
/*   Updated: 2018/08/31 21:32:25 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "wolf3d.h"

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_line
{
	int			height;
	int			start;
	int			end;
}				t_line;

typedef struct	s_ray
{
	t_2d		pos;
	t_2d		init_col;
	t_2d		delta_dist;
	t_2d		side_dist;
	t_line		line;
	t_point		map_pos;
	t_point		step;
	int			side;
	int			texture;
	double		dir;
	double		wall_dist;
	double		sin;
	double		cos;
	double		wall_x;
}				t_ray;

void			raycast(t_game *g);
void			draw_floor(t_ray *ray, t_game *g, int x);
void			draw_sprites(t_ray *ray, t_game *g, int x);
int				get_demo_color(t_ray *ray, t_game *g, int tex_x, int tex_y);
int				get_tex_x(t_ray *ray);

#endif
