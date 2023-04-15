LIBNAME = libutils.a

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -gdwarf-4 -MMD -MP

LIBCREATOR = ar
LIBCREATOR_FLAGS = rsc

OBJDIR = obj
SRCDIR = src
HEADER_DIRS = $(sort $(dir $(wildcard *.h) $(wildcard */*.h) $(wildcard */*/*.h) $(wildcard */*/*/*.h)))

SOURCES = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*/*.c) $(wildcard $(SRCDIR)/*/*/*.c)
OBJECTS = $(subst $(SRCDIR)/,,$(addprefix $(OBJDIR)/, $(SOURCES:.c=.o)))
DEPENDS = $(subst $(SRCDIR)/,,$(addprefix $(OBJDIR)/, $(SOURCES:.c=.d)))

INCLUDE_HEADER_DIRS = $(addprefix -I, $(HEADER_DIRS))

PHONY := all
all: $(LIBNAME)
	@:

$(LIBNAME): $(SOURCES) $(OBJDIR) $(OBJECTS)
	@$(LIBCREATOR) $(LIBCREATOR_FLAGS) $@ $(OBJECTS)
	@printf "$(notdir $@)\tcreated\n"

-include $(DEPENDS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile
	@mkdir -p $(@D)
	@$(CC) $(INCLUDE_HEADER_DIRS) $(CFLAGS) $(LIBGTK) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@

PHONY += clean
clean:
	@rm -rf $(OBJDIR)
	@printf "$(patsubst lib%.a,%,$(LIBNAME))\t\t$@ed\n"

PHONY += uninstall
uninstall: clean
	@rm -rf $(LIBNAME)
	@printf "$(patsubst lib%.a,%,$(LIBNAME))\t\t$@ed\n"

PHONY += reinstall
reinstall: uninstall all

.PHONY: $(PHONY)
