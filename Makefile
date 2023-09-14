BUILD_DIR = build
CC_OPTIONS = -I. -Wall -Wextra

usage:
	@echo "Usage:"
	@echo "    * Build Compiler: 'make build'"
	@echo "    * Run Compiler:   'make run file=<file>'"
	@echo "Tests:"
	@echo "    * Test vec:     'make test_vec_token"
	@echo "    * Test scanner: 'make test_scanner'"

build: setup sv vec_token scanner quote tokenkind token
	@gcc -o $(BUILD_DIR)/main main.c $(CC_OPTIONS) \
		$(BUILD_DIR)/sv.o            \
		$(BUILD_DIR)/scanner.o       \
		$(BUILD_DIR)/vec_token.o     \
		$(BUILD_DIR)/quote.o         \
		$(BUILD_DIR)/token.o         \
		$(BUILD_DIR)/tokenkind.o     \
		$(BUILD_DIR)/keywords.o      \
		

sv:
	@gcc -c tools/sv/sv.c -o $(BUILD_DIR)/sv.o $(CC_OPTIONS) -Itools/sv/

quote: sv
	@gcc -o $(BUILD_DIR)/quote.o -c \
		lex/quote/quote.c           \
		$(CC_OPTIONS) -Ilex/quote/  \

token: sv
	@gcc -o $(BUILD_DIR)/token.o -c \
		lex/token/token.c           \
		$(CC_OPTIONS) -Ilex/token/

tokenkind: sv
	@gcc -o $(BUILD_DIR)/tokenkind.o -c \
		lex/token/tokenkind.c           \
		$(CC_OPTIONS) -Ilex/token       \

vec_token: sv
	@gcc  -o $(BUILD_DIR)/vec_token.o -c \
	tools/vec/token/vec.c                \
	$(CC_OPTIONS) -Itools/vec/token/

test_vec_token: vec_token
	@gcc -o $(BUILD_DIR)/test       \
		tools/vec/test.c            \
		$(BUILD_DIR)/sv.o           \
		$(BUILD_DIR)/vec_token.o    \
		$(CC_OPTIONS)
	@make test EXE=test
	
scanner: vec_token sv keywords
	@gcc -o $(BUILD_DIR)/scanner.o -c \
		lex/scanner/scanner.c         \
		$(CC_OPTIONS) -Ilex/scanner/

keywords:
	@gcc -o $(BUILD_DIR)/keywords.o -c \
		lex/scanner/keywords.c         \
		$(CC_OPTIONS) -Ilex/scanner 

test_scanner: scanner 
	@gcc -o $(BUILD_DIR)/test    \
		lex/scanner/test.c       \
		$(BUILD_DIR)/scanner.o   \
		$(BUILD_DIR)/sv.o        \
		$(BUILD_DIR)/vec_token.o \
		$(CC_OPTIONS)
	@make test EXE=test

run: build
	@echo ""
	@echo "-------------------------"
	@./$(BUILD_DIR)/main $(file)

test:
	./$(BUILD_DIR)/$(EXE)

clean:
	@rm -rf $(BUILD_DIR)

setup:
	@mkdir -p $(BUILD_DIR)


