/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 22:47:24 by pthorell          #+#    #+#             */
/*   Updated: 2018/08/29 22:50:11 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct		s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_rgb;

int					rgb_to_int(int r, int g, int b);
t_rgb				int_to_rgb(int color);
int					div_color(int color, int n);
int					sub_color(int color, int n);
int					shade(int color, double n);

#endif
