#include "tui/menu.h"

t_menu_button	menu_button_init(char *label, void (*action)(void *))
{
	t_menu_button	btn;

	btn.str = label;
	btn.action = action;
	return (btn);
}

t_menu	menu_init(size_t btn_count, t_menu_button *buttons)
{
	t_menu	menu;

	menu.buttons = buttons;
	menu.button_count = btn_count;
	menu.selected_index = 0;
	menu.color_pair = PAIR_GUI;
	menu.highlight_color_pair = PAIR_GUI_HIGHLIGHT;
	return (menu);
}

void	menu_up_index(t_menu *menu)
{
	if (menu->selected_index > 0)
		menu->selected_index--;
}

void	menu_down_index(t_menu *menu)
{
	if (menu->selected_index < menu->button_count - 1)
		menu->selected_index++;
}

void	menu_select(t_menu *menu, void *data)
{
	void (*action)(void *) = menu->buttons[menu->selected_index].action;
	if (action)
		action(data);
}