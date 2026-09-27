/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparison.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:24 by jureix-c          #+#    #+#             */
/*   Updated: 2026/01/03 03:19:47 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/types.h>

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char) *s1 - (unsigned char) *s2);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && *s1 && *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char) *s1 - (unsigned char) *s2);
		s1++;
		s2++;
		n--;
	}
	if (n)
		return ((unsigned char) *s1 - (unsigned char) *s2);
	return (0);
}

int	ft_strnlowercmp(const char *s1, const char *s2, size_t n)
{
	while (n && *s1 && *s2)
	{
		if (ft_tolower(*s1) != ft_tolower(*s2))
			return ((unsigned char) ft_tolower(*s1)
				- (unsigned char) ft_tolower(*s2));
		s1++;
		s2++;
		n--;
	}
	if (n)
	{
		return ((unsigned char) ft_tolower(*s1)
			- (unsigned char) ft_tolower(*s2));
	}
	return (0);
}
