BUILD_DIR = build
CC_OPTIONS = -I. -Wall -Wextra

usage:
	@echo "Usage:"
	@echo "    * Build Compiler: 'make build'"

build: setup
	@gcc -o $(BUILD_DIR)/main main.c $(CC_OPTIONS)

run:
	./$(EXE) $(file) 

clean:
	@rm -rf $(BUILD_DIR)

setup:
	@mkdir -p $(BUILD_DIR)


