/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecast_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 00:47:00 by pthorell          #+#    #+#             */
/*   Updated: 2018/09/01 00:50:54 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#include <stdlib.h>

static void	d_swap(double *i, double *j, int *a, int *b)
{
	int		i_temp;
	double	temp;

	temp = *i;
	*i = *j;
	*j = temp;
	i_temp = *a;
	*a = *b;
	*b = i_temp;
}

t_sprite	create_sprite(double x, double y, int texture, double size)
{
	t_sprite result;

	result.pos.x = x;
	result.pos.y = y;
	result.texture = texture;
	result.size = size;
	return (result);
}

#define RND ((unsigned long)random() % 100)

void		init_sprites(t_game *g)
{
	g->sprites[0] = create_sprite(RND + 10, RND + 10, ENEMY_SPRITE, 1);
	g->sprites[1] = create_sprite(6.5, 3.5, PICKUP_SPRITE, 0.25);
	g->sprites[2] = create_sprite(3.5, 13.5, PICKUP_SPRITE, 0.25);
	g->sprites[3] = create_sprite(2.5, 44.5, PICKUP_SPRITE, 0.25);
	g->sprites[4] = create_sprite(12.5, 21.5, PICKUP_SPRITE, 0.25);
	g->sprites[5] = create_sprite(26.5, 18.5, PICKUP_SPRITE, 0.25);
	g->sprites[6] = create_sprite(32.5, 18.5, PICKUP_SPRITE, 0.25);
	g->sprites[7] = create_sprite(41.5, 31.5, PICKUP_SPRITE, 0.25);
	g->sprites[8] = create_sprite(45.5, 20.5, PICKUP_SPRITE, 0.25);
	g->sprites[9] = create_sprite(43.5, 69.5, EXIT_SPRITE, 1);
}

#define DSTI g->sprite_info.sprite_distance[i]
#define DSTJ g->sprite_info.sprite_distance[i + gap]
#define ORDI g->sprite_info.sprite_order[i]
#define ORDJ g->sprite_info.sprite_order[i + gap]

void		sort_sprites(t_game *g)
{
	int	gap;
	int	swapped;
	int	i;

	gap = SPRITE_COUNT;
	swapped = 0;
	while (gap > 1 || swapped)
	{
		gap = (gap * 10) / 13;
		if (gap == 9 || gap == 10)
			gap = 11;
		if (gap < 1)
			gap = 1;
		swapped = 0;
		i = -1;
		while (++i < SPRITE_COUNT - gap)
		{
			if (DSTI < DSTJ)
			{
				d_swap(&DSTI, &DSTJ, &ORDI, &ORDJ);
				swapped = 1;
			}
		}
	}
}
