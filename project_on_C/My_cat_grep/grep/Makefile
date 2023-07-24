CC = gcc
FLAGS =-Wall -Werror -Wextra -std=c11
LIB = -lpcre
NAME = s21_grep

all: $(NAME)

$(NAME): $(NAME).c $(NAME).h
	$(CC) $(FLAGS) $< $(LIB) -o $@

rebuild:
	$(MAKE) clean
	$(MAKE) all

clean:
	rm -rf $(NAME)