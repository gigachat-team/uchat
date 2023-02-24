LIBNAME = libutils.a

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -gdwarf-4 -MMD -MP

LIBCREATOR = ar
LIBCREATOR_FLAGS = rsc

OBJDIR = obj
SRCDIR = src

SOURCES = $(subst ./,,$(shell find . -name "*.c"))
OBJECTS = $(subst $(SRCDIR)/,,$(addprefix $(OBJDIR)/, $(SOURCES:.c=.o)))
DEPENDS = $(subst $(SRCDIR)/,,$(addprefix $(OBJDIR)/, $(SOURCES:.c=.d)))

all: $(LIBNAME)
	@:

$(LIBNAME): $(SOURCES) $(OBJDIR) $(OBJECTS)
	@$(LIBCREATOR) $(LIBCREATOR_FLAGS) $@ $(OBJECTS)
	@printf "$(notdir $@)\tcreated\n"

-include $(DEPENDS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile
	@$(CC) $(CFLAGS) $(LIBGTK) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJDIR)
	@printf "$(patsubst lib%.a,%,$(LIBNAME))\t\t$@ed\n"
	
uninstall: clean
	@rm -rf $(LIBNAME)
	@printf "$(patsubst lib%.a,%,$(LIBNAME))\t\t$@ed\n"

reinstall: uninstall all

