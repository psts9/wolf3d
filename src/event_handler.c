/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 17:38:33 by pthorell          #+#    #+#             */
/*   Updated: 2018/08/31 17:39:13 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "keys.h"
#include "error.h"
#include "raycast.h"
#include "movement.h"
#include "sprite_controller.h"
#include "timing.h"

#include <math.h>

int	loop_handler(t_game *g)
{
	g->player.rot = fmod(g->player.rot, 360.0);
	if (g->player.rot < 0)
		g->player.rot += 360.0;
	raycast(g);
	move_player(g);
	move_sprites(g);
	display_text(NULL, g);
	return (1);
}

int	key_down(int keycode, t_game *g)
{
	if (keycode == KEY_ESC)
		pexit();
	g->keys[keycode] = 1;
	return (1);
}

int	key_up(int keycode, t_game *g)
{
	g->keys[keycode] = 0;
	return (1);
}

int	motion_handler(int x, int y, t_game *g)
{
	static int prev_x = 0;

	g->player.rot += ((x - prev_x) / 3.0);
	prev_x = x;
	y = 0;
	return (1);
}
