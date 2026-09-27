/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:25 by jureix-c          #+#    #+#             */
/*   Updated: 2025/10/03 22:16:10 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && i + 1 < size)
	{
		dst[i] = src[i];
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dst;

	dst = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dst[i] = s[i];
		++i;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*dst;

	dst = malloc(sizeof(char) * (int_min(ft_strlen(s), n) + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		dst[i] = s[i];
		++i;
	}
	dst[i] = '\0';
	return (dst);
}

char	**dup_string_arr(char **arr)
{
	char	**dup_arr;
	size_t	len;
	size_t	i;

	if (!arr)
		return (NULL);
	len = string_arr_len(arr);
	dup_arr = ft_calloc(len + 1, sizeof(char *));
	if (!dup_arr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup_arr[i] = ft_strdup(arr[i]);
		if (!dup_arr[i++])
		{
			free_string_arr(dup_arr);
			return (NULL);
		}
	}
	return (dup_arr);
}
