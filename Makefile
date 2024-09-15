SHELL=/bin/sh
CC=gcc
CFLAGS=-std=c11 -pedantic -Wall -Werror -Wextra
DEBUG_FLAG= -g
COVFLAGS=-fprofile-arcs -ftest-coverage
DOC=misc/docs

C_FILES = $(wildcard brick_game/tetris/*.c gui/cli/*.c)
C_FILES_BACK = $(wildcard brick_game/tetris/*.c)

O_FILES = $(subst .c,.o, $(C_FILES))

# Директория для тестов
TEST_DIR=./tests/
TEST_FILES=$(wildcard ./tests/*.c)
OUT_TEST =./tests/test.out
OUT_GAME=tetris.out
OS := $(shell uname -s)

# Флаги для линукса отдельно
ifeq ($(OS),Linux)
	OPEN_CMD = xdg-open
	TEST_LIBS = -lcheck -lsubunit -lrt -lm -pthread -lncurses
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
	TEST_LIBS = -lcheck -lncurses
endif

all: install

test: clean
	$(CC) $(CFLAGS) -o ${OUT_TEST} $(C_FILES_BACK) $(TEST_FILES) $(TEST_LIBS)
	$(OUT_TEST)

install: clean
	$(CC) $(CFLAGS) -o ${OUT_GAME} gameLoop.c $(C_FILES) $(TEST_LIBS)
	@echo "Installation complete."

uninstall: clean
	rm -f $(OUT_GAME)
	@echo "Uninstallation complete."

debug: clean
	$(CC) $(CFLAGS) $(DEBUG_FLAG) -o ${OUT_GAME} $(C_FILES) $(TEST_FILES) $(TEST_LIBS)

gcov_report: clean
	$(CC) $(CFLAGS) --coverage $(C_FILES_BACK) $(TEST_FILES) -o $(TEST_DIR)gcov_test $(TEST_LIBS)
	chmod +x *
		$(TEST_DIR)gcov_test
	lcov -t "gcov_test" -o $(TEST_DIR)gcov_test.info --no-external -c -d .
	genhtml -o $(TEST_DIR)report/ $(TEST_DIR)gcov_test.info
	$(OPEN_CMD) $(TEST_DIR)/report/index.html

valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=leaks_log.txt $(OUT_TEST)
	echo --- Valgrind summary --- && cat leaks_log.txt | grep 'total heap usage' && cat leaks_log.txt | grep 'ERROR SUMMARY' 

style_test:
	clang-format -n */*/*.c */*/*.h */*.c */*.h *.c

format_style:
	clang-format -i */*/*.c */*/*.h */*.c */*.h *.c

clean: clean_test
	rm -rf */*.o *.out */*/*.o */*.out */*/*/*.o */*/*.out debug test.out leaks_log.txt docs/ dist/ s21_tetris_dist.tar.gz

clean_test:
	rm -rf *.gc* *.info $(TEST_DIR)*.info $(TEST_DIR)*.gc* $(TEST_DIR)gcov_test $(TEST_DIR)report $(TEST_DIR)*.out

rebuild: clean all

dvi:
	@echo "Building HTML documentation..."
	@if [ ! -f "misc/docs.html" ]; then 								\
		echo "No such file!"; 														\
	else 																								\
		if [ ! -d "docs" ]; then mkdir docs; fi; 					\
		cp misc/docs.html docs/docs.html; 								\
		echo "HTML documentation copied successfully."; 	\
		open docs/docs.html; 															\
	fi

dvi_some:
	@echo "Building DVI documentation..."
	@if [ ! -f "misc/docs.html" ]; then 								\
		echo "No such file!"; 														\
	else 																								\
		if [ ! -d "docs" ]; then mkdir docs; fi; 					\
		htlatex $(DOC).html "xhtml, charset=utf-8" "" -d./\
		mv $(DOC).dvi docs/docs.dvi;											\
		echo "DVI documentation is ready."; 	\
		open docs/docs.html; 															\
	fi
	

dist: clean
	@echo "Creating distribution package..."
	if [ ! -d "docs" ]; then mkdir dist; fi;
	cp -r * dist/
	rm -rf dist/dist/
	tar -czf s21_tetris_dist.tar.gz dist
	rm -rf dist
	@echo "Distribution package created: s21_tetris_dist.tar.gz"

.PHONY: all test install uninstall debug gcov_report valgrind style_test format_style clean clean_test rebuild dvi_mac dvi dist
