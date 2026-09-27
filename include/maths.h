#ifndef MATHS_H
# define MATHS_H

// INCLUDES
# include <stdbool.h>

// STRUCTURES
typedef struct s_vec2
{
	int	x;
	int	y;
}	t_vec2;

// PROTOTYPES
// Vectors
t_vec2	vec2_init(int x, int y);
t_vec2	vec2_add(t_vec2 a, t_vec2 b);

// Random
int		rand_range(int min, int max);
bool	rand_bool(double probability);

#endif
