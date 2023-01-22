LIBMX_DIR = libmx
SQLITE3_DIR = sqlite3

define make_command
	@make --no-print-directory -C
endef

all:
	$(make_command) $(LIBMX_DIR)
	$(make_command) $(SQLITE3_DIR)

clean:
	$(make_command) $(LIBMX_DIR) clean
	$(make_command) $(SQLITE3_DIR) clean

uninstall:
	$(make_command) $(LIBMX_DIR) uninstall
	$(make_command) $(SQLITE3_DIR) uninstall

reinstall:
	$(make_command) $(LIBMX_DIR) reinstall
	$(make_command) $(SQLITE3_DIR) reinstall

