LIBNAME = libsqlite3.a

CC = clang

LIBCREATOR = ar
LIBCREATOR_FLAGS = rsc

OBJDIR = .
SRCDIR = .

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.c=.o)))

PHONY := all
all: $(LIBNAME)
	@:

$(LIBNAME): $(SOURCES) $(OBJECTS)
	@$(LIBCREATOR) $(LIBCREATOR_FLAGS) $@ $(OBJECTS)
	@printf "$(notdir $@)\tcreated\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) -c $< -o $@

PHONY += clean
clean:
	@rm -rf $(OBJECTS)
	@printf "$(patsubst lib%.a,%,$(LIBNAME))\t\t$@ed\n"

PHONY += uninstall
uninstall: clean
	@rm -rf $(LIBNAME)
	@printf "$(patsubst lib%.a,%,$(LIBNAME))\t\t$@ed\n"

PHONY += reinstall
reinstall: uninstall all

.PHONY: $(PHONY)
