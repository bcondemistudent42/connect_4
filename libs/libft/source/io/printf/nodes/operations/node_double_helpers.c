/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_double_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 21:36:35 by jureix-c          #+#    #+#             */
/*   Updated: 2026/03/04 21:43:10 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/nodes.h"
#include "ft_printf/utils.h"

// PROTOTYPES
static uint64_t	ft_pow10(int n);
static uint64_t	round_half_to_even(double scaled);

char	get_double_sign(t_printf_node *node)
{
	if (node->data.f < 0)
		return ('-');
	if (node->flag_plus)
		return ('+');
	if (node->flag_space)
		return (' ');
	return (0);
}

void	get_double_parts(t_printf_node *node, uint64_t *i_part,
		uint64_t *f_part)
{
	double		val;
	uint64_t	pow;

	val = node->data.f;
	if (val < 0)
		val = -val;
	*i_part = (uint64_t)val;
	pow = ft_pow10(node->precision);
	*f_part = round_half_to_even((val - *i_part) * pow);
	if (*f_part >= pow)
	{
		*f_part = 0;
		(*i_part)++;
	}
}

void	get_double_node_lens(t_printf_node *node, int *raw, int *total)
{
	uint64_t	i_part;
	uint64_t	f_part;
	int			local;

	get_double_parts(node, &i_part, &f_part);
	local = uint_strlen(i_part, 10);
	if (node->precision > 0)
		local += 1 + node->precision;
	if (raw)
		*raw = local;
	local += (get_double_sign(node) != 0);
	if (total)
		*total = local;
}

static uint64_t	ft_pow10(int n)
{
	uint64_t	result;

	result = 1;
	while (n-- > 0)
		result *= 10;
	return (result);
}

static uint64_t	round_half_to_even(double scaled)
{
	uint64_t	truncated;
	double		remainder;

	truncated = (uint64_t)scaled;
	remainder = scaled - truncated;
	if (remainder > 0.5)
		return (truncated + 1);
	if (remainder == 0.5 && truncated % 2 != 0)
		return (truncated + 1);
	return (truncated);
}
