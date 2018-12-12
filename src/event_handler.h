/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 17:39:35 by pthorell          #+#    #+#             */
/*   Updated: 2018/08/31 17:39:50 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_HANDLER_H
# define EVENT_HANDLER_H

# include "wolf3d.h"

int	loop_handler(t_game *g);
int	key_down(int keycode, t_game *g);
int	key_up(int keycode, t_game *g);
int	motion_handler(int x, int y, t_game *g);

#endif
