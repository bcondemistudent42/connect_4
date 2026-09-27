/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 23:03:16 by jureix-c          #+#    #+#             */
/*   Updated: 2026/01/04 23:11:09 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "errft.h"

t_error_stack	*error_stack(void)
{
	static t_error_stack	stack = {0};

	return (&stack);
}

t_error_el	*error_stack_get_next_slot(void)
{
	t_error_stack	*stack;

	stack = error_stack();
	if (!stack)
		return (NULL);
	if (stack->cursor >= ERROR_STACK_MAX)
		return (NULL);
	return (stack->stack + stack->cursor++);
}
