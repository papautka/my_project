CC = gcc
FLAGS =-Wall -Werror -Wextra -std=c11
NAME = s21_cat

all: $(NAME)

$(NAME): $(NAME).c $(NAME).h
	$(CC) $(FLAGS) $< -o $@

rebuild:
	$(MAKE) clean
	$(MAKE) all

clean:
	rm -rf $(NAME)