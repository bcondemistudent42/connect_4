/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcondemi <bcondemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:30:26 by bcondemi          #+#    #+#             */
/*   Updated: 2026/09/26 14:29:23 by bcondemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include <unistd.h>
# include <stdlib.h>
#include "../header.h"

size_t	ft_strlen(char *str);

long	ft_get_index(char	*str);

char	*ft_fill_line(int fd, char *output_line, char stock[]);

char	*get_next_line(int fd);

char	*ft_strjoin(char *s1, char s2[]);

void	*ft_check_null(char *str);

void	ft_copy_short(char	*output_line, char stock[], size_t index);

#endif