/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handler.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 00:59:56 by pthorell          #+#    #+#             */
/*   Updated: 2018/09/01 01:00:11 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_HANDLER_H
# define TEXTURE_HANDLER_H

# include "wolf3d.h"

void	load_textures(t_game *g);
int		get_texture_number(char c);

#endif
