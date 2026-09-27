/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_dump_dispatch.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:02:02 by jureix-c          #+#    #+#             */
/*   Updated: 2026/03/04 21:34:27 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/nodes.h"

static int	_dump_buffered_fd(t_printf_data *data, int total_len)
{
	ssize_t	ret;

	ret = write(data->output.fd, data->output.buffer, total_len);
	if (ret < 0)
	{
		data->output.error = PRINTF_OUTPUT_ERROR_IO;
		return (FAILURE);
	}
	else if (ret != (ssize_t) total_len)
	{
		data->output.error = PRINTF_OUTPUT_ERROR_SIZE;
		return (FAILURE);
	}
	return (total_len);
}

static int	_dump_buffered_init(t_printf_data *data, int total_len)
{
	data->output.buffer = malloc(total_len + 1);
	if (!data->output.buffer)
		return (1);
	data->output.size = total_len + 1;
	data->output.cursor = 0;
	return (0);
}

int	dump_nodes(t_printf_data *data)
{
	t_printf_node	*node;
	int				total_len;
	int				res;

	total_len = get_nodes_total_len(data->nodes);
	if (data->output.mode == PRINTF_OUTPUT_BUFFERED_FD)
	{
		if (_dump_buffered_init(data, total_len))
			return (MALLOC_ERROR);
	}
	node = data->nodes;
	while (node)
	{
		res = dump_node(&data->output, node);
		if (res < 0)
		{
			if (res == FAILURE)
				break ;
			return (res);
		}
		node = node->next;
	}
	if (data->output.mode == PRINTF_OUTPUT_BUFFERED_FD)
		return (_dump_buffered_fd(data, total_len));
	return (total_len);
}

int	dump_node(t_printf_output *out, t_printf_node *node)
{
	if (node->type == NODE_TYPE_CHAR)
		return (dump_char_node(out, node));
	if (node->type == NODE_TYPE_STRING)
		return (dump_string_node(out, node));
	if (node->type == NODE_TYPE_POINTER)
		return (dump_pointer_node(out, node));
	if (node->type == NODE_TYPE_INTEGER || node->type == NODE_TYPE_UNSIGNED)
		return (dump_int_node(out, node));
	if (node->type == NODE_TYPE_HEX_LOWER || node->type == NODE_TYPE_HEX_UPPER)
		return (dump_hex_node(out, node));
	if (node->type == NODE_TYPE_DOUBLE)
		return (dump_double_node(out, node));
	if (node->type == NODE_TYPE_WRITTEN_COUNT)
		return (dump_written_count_node(out, node));
	if (node->type == NODE_TYPE_PERCENT)
		return (dump_percent_node(out));
	if (node->type == NODE_TYPE_TEXT)
		return (dump_text_node(out, node));
	return (FAILURE);
}
