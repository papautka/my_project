CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
TEST_FLAGS = -lcheck

BUILD_DIR=build
BUILD_TEST_DIR=$(BUILD_DIR)/tests
SRCS=$(wildcard c_files/*.c)
HDRS=$(wildcard c_files/*.h)
OBJS=$(SRCS:%.c=$(BUILD_DIR)/%.o)
TEST_SRCS=$(wildcard c_files/test/*.c)
UI_FOLDER=$(wildcard ui/*)

all: clean test 

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

test:
	@echo "\033[1;34mCreating tests\033[0m"
	@$(CC) $(FLAGS) $(SRCS) $(TEST_SRCS) $(TEST_FLAGS) -o test
	@./test
	@echo "\033[1;42m DONE \033[0m" 

clean:
	@echo "\033[1;34mCleaning\033[0m"
	@rm -rf build/ gcov_report/ a.out test *.info *.a *.gcda app Dvi *.gcov *.gcno *.gcov *.gcno report
	@echo "\033[1;42m DONE \033[0m"

install:
	@echo "\033[1;34mInstalling\033[0m"
	@mkdir app
	@cp -rf $(SRCS) $(HDRS) $(UI_FOLDER) app
	@cd app/3DViewer_v1 && qmake 3DViewer_v1.pro && make
	@cd app && rm -rf *.o *.c *.cpp *.h
	@cp -r app/3DViewer_v1/3DViewer.app ~/Desktop
	@echo "\033[1;42m DONE \033[0m" 

uninstall:
	@echo "\033[1;34mUnistalling\033[0m"
	@rm -rf app
	@rm -rf ~/Desktop/3DViewer.app ~/Desktop/3DViewer.tar.gz
	@echo "\033[1;42m DONE \033[0m"

gcov_report:
	@$(CC) $(TEST_FLAGS) c_files/test/tests.c $(SRCS) -lcheck -o test --coverage
	@./test
	@gcov *.gcno
	@lcov -t "affine_parcer" -o affine_parcer.info -c -d .
	@genhtml -o report affine_parcer.info
	@open report/index.html

dvi:
	@doxygen config
	@open ./Dvi/html/files.html

dist: uninstall install
	@echo "\033[1;34mArchivating\033[0m"
	@tar -cvzf ~/Desktop/3DViewer.tar.gz ~/Desktop/3DViewer.app
	@echo "\033[1;42m DONE \033[0m"

style: 
	@echo "\033[1;34mStyling\033[0m"
	@cp ../materials/linters/.clang-format ./
	@clang-format -i c_files/*.c c_files/test/*.c
	@clang-format -i c_files/*.h
	@rm -rf .clang-format
	@echo "\033[1;42m DONE \033[0m"