/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 00:53:30 by pthorell          #+#    #+#             */
/*   Updated: 2018/09/01 00:59:37 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "color.h"

#include <stdlib.h>

int			get_texture_number(char c)
{
	int	i;

	i = 0;
	while (TEXTURE_TILES[i] != c && TEXTURE_TILES[i])
		++i;
	if (!TEXTURE_TILES[i])
		return (0);
	else
		return (i + 1);
}

#define BPS img->bits_per_pixel

static int	get_img_color(t_image *img, int x, int y)
{
	t_rgb	rgb;

	rgb.b = img->img_data[x * (BPS / 8) + 0 + y * img->size_line];
	rgb.g = img->img_data[x * (BPS / 8) + 1 + y * img->size_line];
	rgb.r = img->img_data[x * (BPS / 8) + 2 + y * img->size_line];
	return (rgb_to_int(rgb.r, rgb.g, rgb.b));
}

#define SZ TEXTURE_WIDTH * TEXTURE_HEIGHT
#define IBPS i.bits_per_pixel

static void	load_texture(int tex_buff[SZ], char *file, t_game *g)
{
	t_image	i;
	int		w;
	int		h;
	int		x;
	int		y;

	i.image = mlx_xpm_file_to_image(g->window.mlx, file, &w, &h);
	i.img_data = mlx_get_data_addr(i.image, &IBPS, &i.size_line, &i.endian);
	y = 0;
	while (y < TEXTURE_HEIGHT)
	{
		x = 0;
		while (x < TEXTURE_WIDTH)
		{
			tex_buff[(y * TEXTURE_WIDTH) + x] = get_img_color(&i, x, y);
			++x;
		}
		++y;
	}
	mlx_destroy_image(g->window.mlx, i.image);
}

void		load_textures(t_game *g)
{
	load_texture(g->textures[0], "textures/default.xpm", g);
	load_texture(g->textures[1], "textures/wall.xpm", g);
	load_texture(g->textures[2], "textures/roof.xpm", g);
	load_texture(g->textures[3], "textures/red_wall.xpm", g);
	load_texture(g->textures[4], "textures/exit_wall.xpm", g);
	load_texture(g->textures[5], "textures/exit.xpm", g);
	load_texture(g->textures[6], "textures/plant.xpm", g);
	load_texture(g->textures[7], "textures/testsprite.xpm", g);
	load_texture(g->textures[8], "textures/blank.xpm", g);
}
