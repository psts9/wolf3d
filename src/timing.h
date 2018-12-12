/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 01:29:10 by pthorell          #+#    #+#             */
/*   Updated: 2018/09/01 01:29:45 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMING_H
# define TIMING_H

# include "mlx.h"
# include "wolf3d.h"

typedef struct	s_timed_message
{
	char		*text;
	int			length;
}				t_timed_message;

void			display_text(t_timed_message *message, t_game *g);

#endif
