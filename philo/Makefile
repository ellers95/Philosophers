NAME = philo
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c \
initialize_philos.c \
philo_actions.c \
philo_print.c \
philo_utils.c \
run_philo.c

OBJS_DIR = objs/
OBJS = $(SRCS:%.c=%.o)
OBJS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

$(OBJS_DIR)%.o: %.c $(HEADERS)
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS_PREFIXED)
	ar r $(NAME) $(OBJS_PREFIXED)

all: $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: flcean all

.PHONY: all clean fclean re