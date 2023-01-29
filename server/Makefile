BINARYNAME = ../uchat_server

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -gdwarf-4 -pthread

OBJDIR = obj
UTILS_OBJDIR = ../utils/obj
SRCDIR = src

SOURCES = $(subst ./,,$(shell find . -name "*.c"))
OBJECTS = $(subst $(SRCDIR)/,,$(addprefix $(OBJDIR)/, $(SOURCES:.c=.o)))

UTILS_LIB = -L../utils -lutils
SQLITE3_LIB = -L../resources/libraries/sqlite3 -lsqlite3 -ldl
LIBMX_LIB = -L../resources/libraries/libmx -lmx

all: $(BINARYNAME)
	@:

$(BINARYNAME): $(SOURCES) $(OBJDIR) $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) $(UTILS_LIB) $(SQLITE3_LIB) $(LIBMX_LIB) -o $@
	@printf "$(notdir $@)\tcreated\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJDIR)
	@printf "$(notdir $(BINARYNAME))\t$@ed\n"

uninstall: clean
	@rm -rf $(BINARYNAME)
	@printf "$(notdir $(BINARYNAME))\t$@ed\n"

reinstall: uninstall all

