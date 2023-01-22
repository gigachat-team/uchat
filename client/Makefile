BINARYNAME = ../uchat

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -gdwarf-4

OBJDIR = obj
UTILS_OBJDIR = ../utils/obj
SRCDIR = src

SOURCES = $(shell find . -name "*.c")
OBJECTS = $(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.c=.o)))
UTILS_OBJECTS = $(wildcard $(UTILS_OBJDIR)/*.o)
LIBMX_LIB = -L../resources/libraries/libmx -lmx

all: $(BINARYNAME)

$(BINARYNAME): $(SOURCES) $(OBJDIR) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(UTILS_OBJECTS) $(LIBMX_LIB) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@

clean:
	rm -rf $(OBJDIR)

uninstall: clean
	rm -rf $(BINARYNAME)

reinstall: uninstall all

