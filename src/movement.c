/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 19:52:15 by pthorell          #+#    #+#             */
/*   Updated: 2018/09/05 14:42:42 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "keys.h"

#include <math.h>
#include <time.h>

#define POSX g->player.pos.x
#define POSY g->player.pos.y

static void	do_move(double move_x, double move_y, double rot, t_game *g)
{
	if (g->player.pos.x + move_x < g->map.w && g->player.pos.x + move_x > 0)
		if (g->map.map[(int)POSY][(int)(POSX + move_x)] == '.')
			g->player.pos.x += move_x;
	if (g->player.pos.y + move_y < g->map.h && g->player.pos.y + move_y > 0)
		if (g->map.map[(int)(POSY + move_y)][(int)POSX] == '.')
			g->player.pos.y += move_y;
	g->player.rot += rot;
}

static void	do_strafe(double *move_x, double *move_y, t_game *g)
{
	if (g->keys[KEY_A])
	{
		*move_x += sin((g->player.rot) * PI_OVER_180);
		*move_y += cos((g->player.rot) * PI_OVER_180);
	}
	if (g->keys[KEY_D])
	{
		*move_x -= sin((g->player.rot) * PI_OVER_180);
		*move_y -= cos((g->player.rot) * PI_OVER_180);
	}
}

static void	do_walk(double *move_x, double *move_y, double *speed, t_game *g)
{
	if (g->keys[KEY_W] || g->keys[KEY_UP])
	{
		*move_x += sin((g->player.rot + 90) * PI_OVER_180);
		*move_y += cos((g->player.rot + 90) * PI_OVER_180);
		if (g->keys[KEY_SHIFT])
			*speed = 1.8;
	}
	if (g->keys[KEY_S] || g->keys[KEY_DOWN])
	{
		*move_x -= sin((g->player.rot + 90) * PI_OVER_180);
		*move_y -= cos((g->player.rot + 90) * PI_OVER_180);
	}
}

static void	normalize(double *x, double *y)
{
	double w;

	w = sqrt(*x * *x + *y * *y);
	*x /= w;
	*y /= w;
}

void		move_player(t_game *g)
{
	double	move_x;
	double	move_y;
	double	rot;
	double	speed;

	move_x = 0;
	move_y = 0;
	rot = 0;
	speed = 1.0;
	do_walk(&move_x, &move_y, &speed, g);
	do_strafe(&move_x, &move_y, g);
	if (g->keys[KEY_RIGHT])
		rot += 3.0;
	if (g->keys[KEY_LEFT])
		rot -= 3.0;
	normalize(&move_x, &move_y);
	move_x *= speed / 30;
	move_y *= speed / 30;
	do_move(move_x, move_y, rot, g);
}
