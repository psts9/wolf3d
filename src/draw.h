/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 17:34:18 by pthorell          #+#    #+#             */
/*   Updated: 2018/08/31 17:34:36 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "wolf3d.h"

void	put_pixel(int x, int y, int color, t_game *g);
void	draw(t_game *g);
void	clear(t_game *g);

#endif
