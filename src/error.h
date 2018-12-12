/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 17:36:41 by pthorell          #+#    #+#             */
/*   Updated: 2018/08/31 17:37:03 by pthorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

void	simple_error(char *str);
int		pexit(void);
void	perror_exit(char *str);
void	strerror_exit(int err);

#endif
