#ifndef TUI_MENU_H
# define TUI_MENU_H

// INCLUDES
# include "tui/renderer.h"

// STRUCTURES
typedef struct s_menu_button
{
	char	*str;
	void	(*action)(void *);
}	t_menu_button;

typedef struct s_menu
{
	t_menu_button	*buttons;
	t_custom_pair	color_pair;
	t_custom_pair	highlight_color_pair;
	size_t			button_count;
	size_t			selected_index;
}	t_menu;

// PROTOTYPES
t_menu_button	menu_button_init(char *label, void (*action)(void *));
t_menu			menu_init(size_t btn_count, t_menu_button *buttons);
void			menu_up_index(t_menu *menu);
void			menu_down_index(t_menu *menu);
void			menu_select(t_menu *menu, void *data);

#endif
