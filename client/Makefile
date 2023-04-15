BINARYNAME = ../uchat

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -gdwarf-4 -pthread -MMD -MP

OBJDIR = obj
SRCDIR = src
UTILS_DIR = ../utils

HEADER_DIRS = $(sort $(dir $(wildcard *.h) $(wildcard */*.h) $(wildcard */*/*.h) $(wildcard */*/*/*.h)))
UTILS_HEADER_DIRS = $(sort $(dir $(wildcard $(UTILS_DIR)/*.h) $(wildcard $(UTILS_DIR)/*/*.h)))

SOURCES = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*/*.c) $(wildcard $(SRCDIR)/*/*/*.c)
OBJECTS = $(subst $(SRCDIR)/,,$(addprefix $(OBJDIR)/, $(SOURCES:.c=.o)))
DEPENDS = $(subst $(SRCDIR)/,,$(addprefix $(OBJDIR)/, $(SOURCES:.c=.d)))

UTILS_LIB = $(UTILS_DIR)/libutils.a
GTK_LIBS = -rdynamic `pkg-config --cflags --libs gtk+-3.0`
GTK_INC = `pkg-config --cflags gtk+-3.0`

INCLUDE_HEADER_DIRS = $(addprefix -I, $(HEADER_DIRS))
INCLUDE_UTILS_HEADER_DIRS = $(addprefix -I, $(UTILS_HEADER_DIRS))

INCLUDE_UTILS = -L$(dir $(UTILS_LIB)) -l$(patsubst lib%.a,%,$(notdir $(UTILS_LIB)))

PHONY := all
all: $(BINARYNAME)
	@:

$(BINARYNAME): $(SOURCES) $(OBJDIR) $(OBJECTS) $(UTILS_LIB)
	@$(CC) $(CFLAGS) $(OBJECTS) $(INCLUDE_UTILS) -o $@ $(GTK_LIBS)
	@printf "$(notdir $@)\t\tcreated\n"

-include $(DEPENDS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile
	@mkdir -p $(@D)
	@$(CC) $(INCLUDE_HEADER_DIRS) $(INCLUDE_UTILS_HEADER_DIRS) $(GTK_INC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@

PHONY += clean
clean:
	@rm -rf $(OBJDIR)
	@printf "$(notdir $(BINARYNAME))\t\t$@ed\n"

PHONY += uninstall
uninstall: clean
	@rm -rf $(BINARYNAME)
	@printf "$(notdir $(BINARYNAME))\t\t$@ed\n"

PHONY += reinstall
reinstall: uninstall all

.PHONY: $(PHONY)
