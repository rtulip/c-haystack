BUILD_DIR = build
CC_OPTIONS = -I. -Wall -Wextra

usage:
	@echo "Usage:"
	@echo "    * Build Compiler: 'make build'"
	@echo "    * Run Compiler:   'make run file=<file>'"

build: setup sv
	@gcc -o $(BUILD_DIR)/main main.c $(BUILD_DIR)/sv.o $(CC_OPTIONS)

sv:
	@gcc -c tools/sv/sv.c -o $(BUILD_DIR)/sv.o $(CC_OPTIONS) -Itools/sv/

run: build
	@echo ""
	@echo "-------------------------"
	@./$(BUILD_DIR)/main $(file)

clean:
	@rm -rf $(BUILD_DIR)

setup:
	@mkdir -p $(BUILD_DIR)


