CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
TST_LIBS = -lcheck $(shell pkg-config --cflags --libs check)
ifeq ($(shell uname), Linux)
	TST_LIBS += -lpthread -lrt -lsubunit -lm
endif
ifneq (,$(findstring desperos,$(MAKECMDGOALS)))
    DEBUG= -g -DDEBUG -fsanitize=address 
else ifneq (,$(findstring fartlouv,$(MAKECMDGOALS)))
	DEBUG= -g -fsanitize=address
else ifneq (,$(findstring sallieam,$(MAKECMDGOALS)))
	DEBUG= -g -fsanitize=address
else ifneq (,$(findstring catarina,$(MAKECMDGOALS)))
	DEBUG= -g -fsanitize=address
endif
LIB_NAME = s21_math

SRCS=$(wildcard s21_*.c)
OBJS=$(SRCS:.c=.o)

all: clean test

rebuild: all

clean:
	rm -rf *.o test *.a *.gcno *.gcda *.gcov *.html *.css *.info report main/*.o desperos sallieam fartlouv tiaraurz test.dSYM catarina

clang-format:
	clang-format -n -style=Google *.c *.h tests/*.c tests/*.h

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIB_NAME).a: $(OBJS)
	ar rc $(LIB_NAME).a $^
	ranlib $(LIB_NAME).a
	rm -rf *.o

test: clean $(LIB_NAME).a
	$(CC) $(FLAGS) tests/*.c $(LIB_NAME).a $(TST_LIBS) -o test
#	leaks --atExit -- ./$@
	./$@

add_coverage_flag:
	$(eval FLAGS += --coverage)

# gcov_report: add_coverage_flag test
#gcov_report: add_coverage_flag test
#	./test
#	rm check*.gcda check*.gcno
#	gcov -b -l -p -c s21_*.gcno
#	gcovr -o gcov_report.html --html --html-details
#	lcov -t "test" -o test.info -c -d .
#	genhtml -o report test.info
#	open report/index.html

gcov_report: add_coverage_flag test
	./test
	lcov -t “gcov_test” -o test.info --no-external -c -d .
	genhtml -o report/ test.info
	open ./report/index.html

# Desperos main for debug
desperos: clang-format main/desperos.o $(OBJS)
	$(CC) $(FLAGS) $(DEBUG) $(OBJS) main/desperos.o -o $@
#	./$@
main/desperos.o: main/desperos.c
	$(CC) $(FLAGS) $(DEBUG) -c $< -o $@
# end Desperos main for debug

# Catarina main for debug
catarina: clang-format main/catarina.o $(OBJS)
	$(CC) $(FLAGS) $(DEBUG) $(OBJS) main/catarina.o -o $@
	 ./$@
main/catarina.o: main/catarina.c
	$(CC) $(FLAGS) $(DEBUG) -c $< -o $@
# end Catarina main for debug

# Fartlouv main for debug
fartlouv: clang-format main/fartlouv.o $(OBJS)
	$(CC) $(FLAGS) $(DEBUG) $(OBJS) main/fartlouv.o -o $@
	 ./$@
main/fartlouv.o: main/fartlouv.c
	$(CC) $(FLAGS) $(DEBUG) -c $< -o $@
# end Fartlouv main for debug
