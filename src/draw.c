/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 17:33:58 by pthorell          #+#    #+#             */
/*   Updated: 2018/08/31 17:34:00 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "wolf3d.h"
#include "color.h"
#include "libft.h"

#define GBPS g->image.bits_per_pixel
#define GMLX g->window.mlx

void	put_pixel(int x, int y, int color, t_game *g)
{
	t_rgb			rgb;
	unsigned int	n_color;

	n_color = mlx_get_color_value(g->window.mlx, color);
	rgb = int_to_rgb(n_color);
	g->image.img_data[x * (GBPS / 8) + 0 + y * g->image.size_line] = rgb.b;
	g->image.img_data[x * (GBPS / 8) + 1 + y * g->image.size_line] = rgb.g;
	g->image.img_data[x * (GBPS / 8) + 2 + y * g->image.size_line] = rgb.r;
	g->image.img_data[x * (GBPS / 8) + 3 + y * g->image.size_line] = 0;
}

void	draw(t_game *g)
{
	mlx_clear_window(g->window.mlx, g->window.window);
	mlx_put_image_to_window(GMLX, g->window.window, g->image.image, 0, 0);
}

void	clear(t_game *g)
{
	ft_bzero(g->image.img_data, RES_X * RES_Y * 4);
}
