SQLITE3_DIR = sqlite3
LIST_DIR = list

define make_command
	@make -s --no-print-directory -C
endef

PHONY := all
all:
	$(make_command) $(SQLITE3_DIR)
	$(make_command) $(LIST_DIR)

PHONY += clean
clean:
	$(make_command) $(SQLITE3_DIR) clean
	$(make_command) $(LIST_DIR) clean

PHONY += uninstall
uninstall:
	$(make_command) $(SQLITE3_DIR) uninstall
	$(make_command) $(LIST_DIR) uninstall
	$(make_command) $(LIST_DIR) clean

PHONY += reinstall
reinstall:
	$(make_command) $(SQLITE3_DIR) reinstall
	$(make_command) $(LIST_DIR) uninstall
	$(make_command) $(LIST_DIR) clean
	$(make_command) $(LIST_DIR)

.PHONY: $(PHONY)
