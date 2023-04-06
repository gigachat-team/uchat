BINARYNAME = ../uchat_server

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -gdwarf-4 -pthread -MMD -MP

OBJDIR = obj
UTILS_OBJDIR = ../utils/obj
SRCDIR = src

SOURCES = $(wildcard $(SRCDIR).c) $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*/*.c)
OBJECTS = $(subst $(SRCDIR)/,,$(addprefix $(OBJDIR)/, $(SOURCES:.c=.o)))
DEPENDS = $(subst $(SRCDIR)/,,$(addprefix $(OBJDIR)/, $(SOURCES:.c=.d)))

UTILS_LIB = ../utils/libutils.a
SQLITE_LIB = ../resources/libraries/sqlite3/libsqlite3.a

INCLUDE_UTILS = -L$(dir $(UTILS_LIB)) -l$(patsubst lib%.a,%,$(notdir $(UTILS_LIB)))
INCLUDE_SQLITE = -L$(dir $(SQLITE_LIB)) -l$(patsubst lib%.a,%,$(notdir $(SQLITE_LIB))) -ldl

all: $(BINARYNAME)
	@:

$(BINARYNAME): $(SOURCES) $(OBJDIR) $(OBJECTS) $(UTILS_LIB)
	@$(CC) $(CFLAGS) $(OBJECTS) $(INCLUDE_UTILS) $(INCLUDE_SQLITE) -o $@
	@printf "$(notdir $@)\tcreated\n"

-include $(DEPENDS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile
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
