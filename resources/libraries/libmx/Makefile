LIBNAME = libmx.a

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -gdwarf-4

LIBCREATOR = ar
LIBCREATOR_FLAGS = rsc

OBJDIR = obj
SRCDIR = src

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.c=.o)))

all: $(LIBNAME)

$(LIBNAME): $(SOURCES) $(OBJDIR) $(OBJECTS)
	@$(LIBCREATOR) $(LIBCREATOR_FLAGS) $@ $(OBJECTS)
	@printf "$(notdir $@) created\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@

uninstall: clean
	rm -rf $(LIBNAME)

clean:
	rm -rf $(OBJDIR)

reinstall: uninstall all


