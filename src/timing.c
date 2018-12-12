/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 01:00:59 by pthorell          #+#    #+#             */
/*   Updated: 2018/09/05 14:29:58 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "timing.h"
#include "mlx.h"
#include "wolf3d.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000)
#define CURMSG current_message->text

static void	set_time(time_t *prev, time_t *curr, time_t *delta_time)
{
	if (!(*prev))
		*prev = clock();
	*curr = clock();
	*delta_time = *curr - *prev;
	*prev = *curr;
}

static void	free_msg(t_timed_message **msg)
{
	free((*msg)->text);
	free(*msg);
	*msg = NULL;
}

#define MLX g->window.mlx

void		display_text(t_timed_message *new_message, t_game *g)
{
	static t_timed_message	*current_message;
	static time_t			prev = 0;
	time_t					curr;
	time_t					delta_time;

	if (new_message)
	{
		if (current_message && current_message->length > 0)
			free_msg(&current_message);
		current_message = new_message;
	}
	set_time(&prev, &curr, &delta_time);
	if (current_message)
	{
		mlx_string_put(MLX, g->window.window, 16, 10, 16777215, CURMSG);
		current_message->length -= (delta_time / CLOCKS_PER_MS);
		if (current_message->length <= 0)
			free_msg(&current_message);
	}
}
