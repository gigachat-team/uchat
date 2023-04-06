SQLITE3_DIR = sqlite3

define make_command
	@make --no-print-directory -C
endef

PHONY := all
all:
	$(make_command) $(SQLITE3_DIR)

PHONY += clean
clean:
	$(make_command) $(SQLITE3_DIR) clean

PHONY += uninstall
uninstall:
	$(make_command) $(SQLITE3_DIR) uninstall

PHONY += reinstall
reinstall:
	$(make_command) $(SQLITE3_DIR) reinstall

.PHONY: $(PHONY)
