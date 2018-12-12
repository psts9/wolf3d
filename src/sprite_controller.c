/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 21:33:45 by pthorell          #+#    #+#             */
/*   Updated: 2018/08/31 21:55:02 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "raycast.h"
#include "error.h"
#include "libft.h"
#include "texture_handler.h"
#include "timing.h"

#include <math.h>
#include <stdlib.h>

#define POSX g->player.pos.x
#define POSY g->player.pos.y

static void	put_msg(char *str, t_game *g)
{
	t_timed_message *message;

	message = malloc(sizeof(*message));
	message->length = PICKUP_MSG_TIME * 1000;
	message->text = ft_strnew(ft_strlen(str) + 1);
	ft_strcpy(message->text, str);
	display_text(message, g);
}

static void	pickup_msg(int score, t_game *g)
{
	char *str;

	str = ft_strnew(24);
	str[0] = '0' + score;
	ft_strcpy(str + 1, " / 8 things collected!");
	put_msg(str, g);
	free(str);
}

static void	do_pickup(t_game *g, int i, double dist)
{
	if (dist < COLLIDE_RANGE)
	{
		if (++g->player.score < PICKUP_COUNT)
			pickup_msg(g->player.score, g);
		else
			put_msg("Good job friend :). Now find the exit", g);
		g->sprites[i].pos.x = -1;
		g->sprites[i].pos.y = -1;
	}
}

static void	do_enemy(t_game *g, int i, double dist)
{
	double angle;
	double var_speed;

	if (dist < COLLIDE_RANGE)
		simple_error("You're dead!");
	angle = atan2(g->sprites[i].pos.y - POSY, g->sprites[i].pos.x - POSX);
	var_speed = ENEMY_SPEED * (g->player.score / (double)PICKUP_COUNT / 2.0);
	g->sprites[i].pos.x -= sin(angle + 1.5708) * (ENEMY_SPEED + var_speed);
	g->sprites[i].pos.y += cos(angle + 1.5708) * (ENEMY_SPEED + var_speed);
}

void		move_sprites(t_game *g)
{
	int		i;
	double	dist;
	double	distx;
	double	disty;

	i = 0;
	while (i < SPRITE_COUNT)
	{
		distx = (g->sprites[i].pos.x - g->player.pos.x);
		disty = (g->sprites[i].pos.y - g->player.pos.y);
		dist = sqrt(distx * distx + disty * disty);
		if (g->sprites[i].texture == ENEMY_SPRITE)
			do_enemy(g, i, dist);
		if (g->sprites[i].texture == PICKUP_SPRITE)
			do_pickup(g, i, dist);
		if (g->sprites[i].texture == EXIT_SPRITE)
		{
			if (dist < COLLIDE_RANGE && g->player.score == PICKUP_COUNT)
				simple_error("You win!");
		}
		++i;
	}
}
