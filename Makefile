CLIENT_BINARY = uchat
SERVER_BINARY = uchat_server

CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

OBJDIR = obj
SRCDIR = src

CLIENT_OBJDIR = $(OBJDIR)/client
SERVER_OBJDIR = $(OBJDIR)/server
CLIENT_SRCDIR = $(SRCDIR)/client
SERVER_SRCDIR = $(SRCDIR)/server

CLIENT_SOURCES = $(wildcard $(CLIENT_SRCDIR)/*.c)
SERVER_SOURCES = $(wildcard $(SERVER_SRCDIR)/*.c)
CLIENT_OBJECTS = $(addprefix $(CLIENT_OBJDIR)/,$(notdir $(CLIENT_SOURCES:.c=.o)))
SERVER_OBJECTS = $(addprefix $(SERVER_OBJDIR)/,$(notdir $(SERVER_SOURCES:.c=.o)))

all: $(CLIENT_BINARY) $(SERVER_BINARY)

$(SERVER_BINARY): $(SERVER_SOURCES) $(SERVER_OBJDIR) $(SERVER_OBJECTS)
	$(CC) $(CFLAGS) $(SERVER_OBJECTS) -o $@

$(CLIENT_BINARY): $(CLIENT_SOURCES) $(CLIENT_OBJDIR) $(CLIENT_OBJECTS)
	$(CC) $(CFLAGS) $(CLIENT_OBJECTS) -o $@	

$(SERVER_OBJDIR)/%.o: $(SERVER_SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(CLIENT_OBJDIR)/%.o: $(CLIENT_SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SERVER_OBJDIR):
	mkdir -p $@

$(CLIENT_OBJDIR):
	mkdir -p $@


# $(BINARYNAME): create_objdir $(OBJECTS)
# 	make -C libmx
# 	$(CC) $(CFLAGS) $(OBJECTS) -Llibmx -lmx -o $@


	
# uninstall: clean
# 	rm -rf $(BINARYNAME)

# clean:
# 	rm -rf $(OBJDIR)

# reinstall: uninstall all



#!/bin/sh -e
#clang -std=c11 -Wall -Wextra -Werror -Wpedantic -c *.c
#ar cr minilibmx.a *.o
#rm -f *.o
#ranlib minilibmx.a

