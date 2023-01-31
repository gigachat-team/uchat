BINARYNAME = ../uchat_server

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -gdwarf-4 -pthread

OBJDIR = obj
UTILS_OBJDIR = ../utils/obj
SRCDIR = src

SOURCES = $(subst ./,,$(shell find . -name "*.c"))
OBJECTS = $(subst $(SRCDIR)/,,$(addprefix $(OBJDIR)/, $(SOURCES:.c=.o)))

UTILS_LIB = ../utils/libutils.a
LIBMX_LIB = ../resources/libraries/libmx/libmx.a
SQLITE_LIB = ../resources/libraries/sqlite3/libsqlite3.a

INCLUDE_UTILS = -L$(dir $(UTILS_LIB)) -l$(patsubst lib%.a,%,$(notdir $(UTILS_LIB)))
INCLUDE_LIBMX = -L$(dir $(LIBMX_LIB)) -l$(patsubst lib%.a,%,$(notdir $(LIBMX_LIB)))
INCLUDE_SQLITE = -L$(dir $(SQLITE_LIB)) -l$(patsubst lib%.a,%,$(notdir $(SQLITE_LIB))) -ldl

all: $(BINARYNAME)
	@:

$(BINARYNAME): $(SOURCES) $(OBJDIR) $(OBJECTS) $(UTILS_LIB)
	@$(CC) $(CFLAGS) $(OBJECTS) $(INCLUDE_UTILS) $(INCLUDE_LIBMX) $(INCLUDE_SQLITE) -o $@
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

