LIBNAME = libsqlite3.a

CC = clang

LIBCREATOR = ar
LIBCREATOR_FLAGS = rsc

OBJDIR = .
SRCDIR = .

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.c=.o)))

all: $(LIBNAME)
	@:

$(LIBNAME): $(SOURCES) $(OBJDIR) $(OBJECTS)
	@$(LIBCREATOR) $(LIBCREATOR_FLAGS) $@ $(OBJECTS)
	@printf "$(notdir $@)\tcreated\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJECTS)
	@printf "$(patsubst %.a,%,$(LIBNAME))\t$@ed\n"

uninstall: clean
	@rm -rf $(LIBNAME)
	@printf "$(patsubst %.a,%,$(LIBNAME))\t$@ed\n"

reinstall: uninstall all

