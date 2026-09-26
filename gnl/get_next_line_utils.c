/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcondemi <bcondemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:30:23 by bcondemi          #+#    #+#             */
/*   Updated: 2026/09/26 14:27:27 by bcondemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

long	ft_get_index(char	*str)
{
	long	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_fill_line(int fd, char *output_line, char stock[])
{
	long		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0 && (long)ft_get_index(output_line) == -1)
	{
		bytes_read = read(fd, stock, BUFFER_SIZE);
		if (bytes_read == 0)
		{
			stock[0] = 0;
			break ;
		}
		if (bytes_read == -1 || !output_line)
		{
			stock[0] = 0;
			free(output_line);
			return (NULL);
		}
		stock[bytes_read] = 0;
		output_line = ft_strjoin(output_line, stock);
	}
	return (output_line);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str || str[0] == '\0')
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char s2[])
{
	char	*ptr;
	int		i;
	int		j;

	i = -1;
	ptr = malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (ptr == NULL)
	{
		free(s1);
		return (NULL);
	}
	if (s1 != NULL)
		while (s1[++i])
			ptr[i] = s1[i];
	free(s1);
	j = -1;
	if (s2 != NULL)
		while (s2[++j])
			ptr[i + j] = s2[j];
	ptr[i + j] = 0;
	return (ptr);
}

void	ft_copy_short(char	*output_line, char stock[], size_t index)
{
	size_t	i;
	long	temp;

	i = 0;
	temp = index;
	index++;
	while (index <= ft_strlen(output_line) -1)
		stock[i++] = output_line[index++];
	stock[i] = 0;
	output_line[temp + 1] = 0;
}
