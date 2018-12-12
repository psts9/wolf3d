/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 19:45:44 by pthorell          #+#    #+#             */
/*   Updated: 2018/08/31 19:51:33 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"
#include "get_map.h"
#include "error.h"
#include "sprites.h"
#include "event_handler.h"
#include "texture_handler.h"

#include <math.h>
#include <stdlib.h>

#define POSX g->player.pos.x
#define POSY g->player.pos.y
#define IIMG g->image.image
#define IBPS g->image.bits_per_pixel
#define ISZL g->image.size_line
#define IEND g->image.endian

static void	init_keys(t_game *g)
{
	int i;

	i = 0;
	while (i < 512)
		g->keys[i++] = 0;
}

static void	init_player(t_game *g)
{
	g->player.pos.x = 1.5;
	g->player.pos.y = 1.5;
	if (g->map.w < (int)ceil(POSX) || g->map.h < (int)ceil(POSY))
		simple_error("Error: Player is spawning outside of the map!");
	g->player.rot = 0.1;
	g->player.score = 0;
}

static void	set_hooks(t_game *g)
{
	mlx_do_key_autorepeatoff(g->window.mlx);
	mlx_loop_hook(g->window.mlx, &loop_handler, g);
	mlx_hook(g->window.window, 2, 0, &key_down, g);
	mlx_hook(g->window.window, 3, 0, &key_up, g);
	mlx_hook(g->window.window, 6, 0, &motion_handler, g);
	mlx_hook(g->window.window, 17, 0, &pexit, g);
}

static void	initialize(t_game *g, char **argv)
{
	get_map(argv[1], g);
	if (!(g->window.mlx = mlx_init()))
		simple_error("Cannot initialize mlx!");
	load_textures(g);
	g->window.window = mlx_new_window(g->window.mlx, RES_X, RES_Y, argv[0]);
	g->image.image = mlx_new_image(g->window.mlx, RES_X, RES_Y);
	g->image.img_data = mlx_get_data_addr(IIMG, &IBPS, &ISZL, &IEND);
	set_hooks(g);
	init_keys(g);
	init_player(g);
	init_sprites(g);
}

int			main(int argc, char **argv)
{
	t_game g;

	srandomdev();
	if (argc < 2)
		simple_error("Usage: wolf3d map");
	else if (argc > 2)
		simple_error("Too many arguments");
	initialize(&g, argv);
	mlx_loop(g.window.mlx);
	return (0);
}
