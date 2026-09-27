#ifndef TUI_RENDERER_H
# define TUI_RENDERER_H

// INCLUDES
# include <stdbool.h>
# include <ncurses.h>

# include "maths.h"

// DEFINES
# define MIN_TERM_HEIGHT 20
# define MIN_TERM_WIDTH 40

# define CELL_WIDTH 4
# define CELL_HEIGHT 2

// ENUMS
typedef enum e_custom_pair
{
	PAIR_COMPUTER = 1,
	PAIR_PLAYER,
	PAIR_GUI,
	PAIR_GUI_HIGHLIGHT,
	PAIR_CURSOR,
	PAIR_END,
}	t_custom_pair;

typedef enum s_ui_type
{
	UI_LABEL,
	UI_BTN,
}	t_ui_type;

// STRUCTURES
typedef struct s_ui_label
{
	char			*str;
	t_custom_pair	color;
}	t_ui_label;

typedef struct s_ui_btn
{
	char			*str;
	t_custom_pair	color;
	t_vec2			size;
}	t_ui_btn;

typedef struct s_ui_element
{
	t_vec2		pos;
	t_vec2		prev_pos;
	bool		should_update;
	t_ui_type	type;
	union
	{
		t_ui_label	label;
		t_ui_btn	btn;
	};
}	t_ui_element;

// PROTOTYPES
// UI Render
int				render_ui(t_ui_element **elements);
int				render_ui_label(t_ui_element *label);
int				render_ui_btn(t_ui_element *btn);

// UI Init
t_ui_element	*init_ui_label(t_vec2 pos, char *str);
t_ui_element	*init_ui_btn(t_vec2 pos, char *str, t_vec2 size);
void			free_ui_element(t_ui_element *element);
void			free_ui_label(t_ui_element *label);
void			free_ui_btn(t_ui_element *btn);

// Utils
int				init_ncurses(void);
int				init_colors(void);
void			free_ncurses(void);

#endif
