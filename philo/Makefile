NAME = philo
CFLAGS = -Wall -Wextra -Werror -g

SRCS = main.c \
initialize_philos.c \
mutexes.c \
philo_print.c \
philo_utils.c \
philo_libft_utils.c \
run_philo.c

HEADERS = philo.h
OBJS_DIR = objs/
OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)

$(OBJS_DIR)%.o: %.c $(HEADERS)
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -pthread

all: $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re