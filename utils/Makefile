LIBNAME = libutils.a

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -gdwarf-4 -MMD -MP

LIBCREATOR = ar
LIBCREATOR_FLAGS = rsc

OBJDIR = obj
SRCDIR = src
LIST_DIR = ../resources/libraries/list
LIST_SRCDIR = $(LIST_DIR)/src
LIST_OBJDIR = $(LIST_DIR)/src

HEADER_DIRS = $(sort $(dir $(wildcard *.h) $(wildcard */*.h) $(wildcard */*/*.h) $(wildcard */*/*/*.h)))
LIST_HEADER_DIRS = $(sort $(dir $(wildcard $(LIST_DIR)/*.h) $(wildcard $(LIST_DIR)/*/*.h)))

SOURCES = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*/*.c) $(wildcard $(SRCDIR)/*/*/*.c)
LIST_SOURCES = $(wildcard $(LIST_SRCDIR)/*.c) $(wildcard $(LIST_SRCDIR)/*/*.c)
OBJECTS = $(subst $(SRCDIR)/,,$(addprefix $(OBJDIR)/, $(SOURCES:.c=.o)))
LIST_OBJECTS = $(LIST_SOURCES:.c=.o)
DEPENDS = $(subst $(SRCDIR)/,,$(addprefix $(OBJDIR)/, $(SOURCES:.c=.d)))


INCLUDE_HEADER_DIRS = $(addprefix -I, $(HEADER_DIRS))
INCLUDE_LIST_HEADER_DIRS = $(addprefix -I, $(LIST_HEADER_DIRS))
INCLUDE_ALL_HEADER_DIRS = $(INCLUDE_HEADER_DIRS) $(INCLUDE_LIST_HEADER_DIRS)

PHONY := all
all: $(LIBNAME)
	@:

$(LIBNAME): $(SOURCES) $(LIST_SOURCES) $(OBJDIR) $(OBJECTS) $(LIST_OBJECTS)
	@$(LIBCREATOR) $(LIBCREATOR_FLAGS) $@ $(OBJECTS) $(LIST_OBJECTS)
	@printf "$(notdir $@)\tcreated\n"

-include $(DEPENDS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile
	@mkdir -p $(@D)
	@$(CC) $(INCLUDE_ALL_HEADER_DIRS) $(CFLAGS) -c $< -o $@

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
