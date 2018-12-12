/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 00:52:13 by pthorell          #+#    #+#             */
/*   Updated: 2018/09/01 00:52:32 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

# include "wolf3d.h"

typedef struct	s_spritecast
{
	int			tex_floor;
	int			draw_end_x;
	int			draw_end_y;
	int			draw_start_x;
	int			draw_start_y;
	double		dir;
	double		dist;
	double		height;
	double		screen_x;
}				t_spritecast;

void			init_sprites(t_game *g);
void			sort_sprites(t_game *g);

#endif
