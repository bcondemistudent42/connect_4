/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:06:00 by jureix-c          #+#    #+#             */
/*   Updated: 2026/01/06 03:39:11 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRFT_H
# define ERRFT_H

// INCLUDES
# include <stdint.h>
# include <stdbool.h>

// DEFINES
# define FL __FILE__
# define LN __LINE__

# define ERROR_STACK_MAX 64

// Errors
typedef int	t_error;
# define SUCCESS 0
# define GENERIC_FAILURE 1
# define MEMORY_FAILURE 2

// STRUCTURES
typedef struct s_error_el
{
	t_error		error;
	int			line_number;
	char		*file;
	void		*optional;
}	t_error_el;

typedef struct s_error_stack
{
	t_error_el	stack[ERROR_STACK_MAX];
	uint32_t	cursor;
}	t_error_stack;

// PROTOTYPES
// Base
t_error			ret(t_error current, char *fl, int ln);
t_error			reto(t_error current, char *fl, int ln, void *optional);

// Utils
t_error_el		*error_stack_find(t_error err);
t_error_stack	*error_stack_dup(void);
void			clean_error_stack(void);

// Internal
t_error_stack	*error_stack(void);
t_error_el		*error_stack_get_next_slot(void);

#endif
