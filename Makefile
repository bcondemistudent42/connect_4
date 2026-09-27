# Base params
MAIN = connect4
CFLAGS = -Wall -Wextra -Werror
NORELINK = -MD -MP
INCLUDE = -I include -I libs/libft/include
SRCDIR = source
BUILDDIR = build

LIBFT = libs/libft/libft.a

include sources.mk

OBJS = $(SRCS:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)
DEPS = $(OBJS:.o=.d)

MAKEFLAGS += --no-print-directory

.DEFAULT_GOAL = all

# Base rules
.PHONY: all
all: $(MAIN)

$(MAIN): $(LIBFT) $(OBJS)
	@echo -n "\033[3;90m🔨 "
	$(CC) $(CFLAGS) $(NORELINK) $(INCLUDE) -o $@ $^ $(LIBFT)
	@echo -n "\033[0m \n \033[32;40;1m✅ Build done!\033[0m\n"

%/:
	mkdir -p $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@echo -n "\033[3;90m🔨 "
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(NORELINK) $(INCLUDE) -o $@ -c $<
	@echo -n "\033[0m"

.PHONY: clean fclean
clean:
	@$(MAKE) clean -C ./libs/libft > /dev/null
	@echo -n "\033[1;91m🗑️  "
	$(RM) -r $(BUILDDIR)
	@echo -n "\033[0m"

fclean: clean
	@$(MAKE) fclean -C ./libs/libft > /dev/null
	@echo -n "\033[1;91m🗑️  "
	$(RM) $(MAIN)
	@echo -n "\033[0m"

.PHONY: re
re: fclean all

# Libs
.PHONY: FORCE
FORCE:

$(LIBFT): FORCE
	@$(MAKE) -C ./libs/libft

# Utils
.PHONY: debug
debug: CFLAGS = -Wall -Wextra -g3 -DDEBUG
debug: all

.PHONY: todo
todo:
	grep -irn --color=always "TODO\|FIXME" source/ include/

-include $(DEPS)
