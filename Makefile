NAME			= philo

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
CFLAGS			+=	-pthread -g3 -fsanitize=thread
CFLAGS			+=	-g
INCLUDES		=	-I./includes

SRCS_DIR		=	srcs
OBJS_DIR		=	objs
CORE_DIR		=	core
THREADS_DIR		=	threads
PARSING_DIR		=	parsing

SRC_FILES		=	main.c							\
            		$(CORE_DIR)/simulation.c		\
            		$(CORE_DIR)/table.c				\
					$(CORE_DIR)/cleanup.c			\
            		$(THREADS_DIR)/actions.c		\
            		$(THREADS_DIR)/routine.c		\
            		$(THREADS_DIR)/monitor.c		\
            		$(THREADS_DIR)/time.c			\
            		$(PARSING_DIR)/ft_atoi.c		\
            		$(PARSING_DIR)/parse.c			\

OBJ_FILES		=	$(SRC_FILES:.c=.o)

SRCS			=	$(addprefix $(SRCS_DIR)/,$(SRC_FILES))
OBJS			=	$(addprefix $(OBJS_DIR)/,$(OBJ_FILES))

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -fr $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

valgrind: fclean
	@$(MAKE) -s CFLAGS="-Wall -Wextra -Werror -pthread -g3" all
	@echo '#!/bin/bash' > run_valgrind.sh
	@echo 'valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./philo $$@' >> run_valgrind.sh
	@chmod +x run_valgrind.sh
	@echo "\033[1;32m✓ Created:\033[0m \033[1;33mrun_valgrind.sh\033[0m"
	@echo "\033[1;34m➜ Run with:\033[0m \033[1;36m./run_valgrind.sh [args]\033[0m"

.PHONY: all clean fclean re valgrind
