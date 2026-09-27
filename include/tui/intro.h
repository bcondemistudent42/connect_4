#ifndef TUI_INTRO_H
# define TUI_INTRO_H

// ENUMS
typedef enum e_intro_anim
{
	INTRO_FLASH = 0,
	INTRO_UP,
}	t_intro_anim;

// STRUCTURES
typedef struct s_state	t_state;

typedef struct s_intro_context
{
	t_state			*state;
	t_intro_anim	animation;
	short			step;
}	t_intro_ctx;

// PROTOTYPES
void	intro_ctx_init(t_intro_ctx *ctx, t_state *state);
void	intro_render(t_intro_ctx *ctx);

#endif
