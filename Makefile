LIBRARIES_DIR = resources/libraries
UTILS_DIR = utils
CLIENT_DIR = client
SERVER_DIR = server

define make_command
	@make --no-print-directory -C
endef

PHONY := all
all:
	$(make_command) $(LIBRARIES_DIR)
	$(make_command) $(UTILS_DIR)
	$(make_command) $(CLIENT_DIR)
	$(make_command) $(SERVER_DIR)

PHONY += clean
clean:
	$(make_command) $(LIBRARIES_DIR) clean
	$(make_command) $(UTILS_DIR) clean
	$(make_command) $(CLIENT_DIR) clean
	$(make_command) $(SERVER_DIR) clean

PHONY += uninstall
uninstall:
	$(make_command) $(UTILS_DIR) uninstall
	$(make_command) $(CLIENT_DIR) uninstall
	$(make_command) $(SERVER_DIR) uninstall

PHONY += uninstall_with_libs
uninstall_with_libs: uninstall
	$(make_command) $(LIBRARIES_DIR) uninstall

PHONY += reinstall
reinstall:
	$(make_command) $(UTILS_DIR) reinstall
	$(make_command) $(CLIENT_DIR) reinstall
	$(make_command) $(SERVER_DIR) reinstall

PHONY += reinstall_with_libs
reinstall_with_libs:
	$(make_command) $(LIBRARIES_DIR) reinstall
	$(make_command) $(UTILS_DIR) reinstall
	$(make_command) $(CLIENT_DIR) reinstall
	$(make_command) $(SERVER_DIR) reinstall

.PHONY: $(PHONY)
