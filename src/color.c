/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 21:02:30 by pthorell          #+#    #+#             */
/*   Updated: 2018/08/29 22:47:12 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int		rgb_to_int(int r, int g, int b)
{
	int rgb;

	rgb = r;
	rgb = (rgb << 8) + g;
	rgb = (rgb << 8) + b;
	return (rgb);
}

t_rgb	int_to_rgb(int color)
{
	t_rgb rgb;

	rgb.r = (color >> 16) & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.b = color & 0xFF;
	return (rgb);
}

int		div_color(int color, int n)
{
	t_rgb rgb;

	rgb = int_to_rgb(color);
	rgb.r /= n;
	rgb.g /= n;
	rgb.b /= n;
	return (rgb_to_int(rgb.r, rgb.g, rgb.b));
}

int		sub_color(int color, int n)
{
	t_rgb rgb;

	rgb = int_to_rgb(color);
	if (rgb.r > n)
		rgb.r -= n;
	else
		rgb.r = 0;
	if (rgb.g > n)
		rgb.g -= n;
	else
		rgb.g = 0;
	if (rgb.b > n)
		rgb.b -= n;
	else
		rgb.b = 0;
	return (rgb_to_int(rgb.r, rgb.g, rgb.b));
}

int		shade(int color, double n)
{
	t_rgb rgb;

	rgb = int_to_rgb(color);
	if (n > 1.0)
		n = 1.0;
	else if (n < 0.0)
		n = 0;
	rgb.r *= n;
	rgb.g *= n;
	rgb.b *= n;
	return (rgb_to_int(rgb.r, rgb.g, rgb.b));
}
