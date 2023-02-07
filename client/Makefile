BINARYNAME = ../uchat

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -gdwarf-4 -pthread -MMD -MP

OBJDIR = obj
UTILS_OBJDIR = ../utils/obj
SRCDIR = src

SOURCES = $(subst ./,,$(shell find . -name "*.c"))
OBJECTS = $(subst $(SRCDIR)/,,$(addprefix $(OBJDIR)/, $(SOURCES:.c=.o)))
DEPENDS = $(subst $(SRCDIR)/,,$(addprefix $(OBJDIR)/, $(SOURCES:.c=.d)))

UTILS_LIB = ../utils/libutils.a
LIBMX_LIB = ../resources/libraries/libmx/libmx.a

INCLUDE_UTILS = -L$(dir $(UTILS_LIB)) -l$(patsubst lib%.a,%,$(notdir $(UTILS_LIB)))
INCLUDE_LIBMX = -L$(dir $(LIBMX_LIB)) -l$(patsubst lib%.a,%,$(notdir $(LIBMX_LIB)))

all: $(BINARYNAME)
	@:

$(BINARYNAME): $(SOURCES) $(OBJDIR) $(OBJECTS) $(UTILS_LIB)
	@$(CC) $(CFLAGS) $(OBJECTS) $(INCLUDE_UTILS) $(INCLUDE_LIBMX) -o $@
	@printf "$(notdir $@)\t\tcreated\n"

-include $(DEPENDS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJDIR)
	@printf "$(notdir $(BINARYNAME))\t\t$@ed\n"

uninstall: clean
	@rm -rf $(BINARYNAME)
	@printf "$(notdir $(BINARYNAME))\t\t$@ed\n"

reinstall: uninstall all

