BUILD_DIR = build
CC_OPTIONS = -I. -Wall -Wextra

usage:
	@echo "Usage:"
	@echo "    * Build Compiler: 'make build'"
	@echo "    * Run Compiler:   'make run file=<file>'"

build: setup
	@gcc -o $(BUILD_DIR)/main main.c $(CC_OPTIONS)

run: build
	./$(BUILD_DIR)/main $(file) 

clean:
	@rm -rf $(BUILD_DIR)

setup:
	@mkdir -p $(BUILD_DIR)


