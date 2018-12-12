/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 17:36:08 by pthorell          #+#    #+#             */
/*   Updated: 2018/08/31 17:36:30 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "libft.h"

void	simple_error(char *str)
{
	ft_putendl(str);
	exit(0);
}

int		pexit(void)
{
	exit(0);
	return (-1);
}

void	perror_exit(char *str)
{
	perror(str);
	exit(0);
}

void	strerror_exit(int err)
{
	strerror(err);
	exit(0);
}
