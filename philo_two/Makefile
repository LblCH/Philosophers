NAME = philo_two

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

LIBS = -lphtread

SRCS = main.c utils.c threads.c init.c

OBJS = $(SRCS:.c=.o)

$(%.o): $(%.c)
	$(CC) -o $@ -c $^

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	@echo "\nDeleting binaries..."
	@rm -f $(OBJS)
	@echo "\033[0m"

fclean:
	@echo "\033[0;31m"
	@echo "\nDeleting objects..."
	@rm -f $(OBJS)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all