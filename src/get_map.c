/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 19:02:28 by pthorell          #+#    #+#             */
/*   Updated: 2018/08/31 19:31:17 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "libft.h"
#include "wolf3d.h"
#include "error.h"

#define MAP_F "Error: The given map is invalid for some reason!"

static void	init_getmap(char **file, int *height, int *prev_width, t_game *g)
{
	int i;

	i = 0;
	while (file[i])
		++i;
	if (!i)
		simple_error(MAP_F);
	*height = i;
	*prev_width = 0;
	if (!(g->map.map = malloc((*height + 1) * sizeof(char*))))
		strerror_exit(errno);
}

static int	get_width(char *str)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (str[i] == ' ' || str[i] == '\t')
		++i;
	while (str[i])
	{
		if (ft_isprint(str[i]) && (str[i] != ' ' && str[i] != '\t'))
		{
			++n;
			++i;
		}
		else if (str[i] == ' ' || str[i] == '\t')
			++i;
		else if (str[i])
			return (-1);
	}
	return (n);
}

static void	get_map_line(char *str, char **arr)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]) && (str[i] != ' ' && str[i] != '\t'))
			(*arr)[n++] = str[i];
		++i;
	}
	(*arr)[n] = '\0';
}

static void	file_to_map(char **file, t_game *g)
{
	int height;
	int prev_width;
	int width;
	int i;

	init_getmap(file, &height, &prev_width, g);
	i = -1;
	while (++i < height)
	{
		if ((width = get_width(file[i])) <= 0)
			simple_error(MAP_F);
		if (!prev_width)
			prev_width = width;
		else if (prev_width != width)
			simple_error(MAP_F);
		if (!(g->map.map[i] = malloc((width + 1) * sizeof(char))))
			strerror_exit(errno);
		get_map_line(file[i], &(g->map.map[i]));
		free(file[i]);
	}
	g->map.map[height] = NULL;
	g->map.h = height;
	g->map.w = width;
	free(file);
}

void		get_map(char *filename, t_game *g)
{
	char	**file;
	char	*str;

	if (!(str = file_to_str(filename)))
		perror_exit(filename);
	if (!(file = ft_strsplit(str, '\n')))
		strerror_exit(errno);
	free(str);
	file_to_map(file, g);
}
