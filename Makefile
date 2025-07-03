NAME			= philo
CC				= cc
CFLAGS			= -Wall -Wextra -Werror
INCLUDES		= -I./includes
SRCS_DIR		= srcs
OBJS_DIR		= objs

SRC_FILES		=	main.c			\
					philosophers.c	\
					simulation.c	\
					utils.c			\
					parse.c			\
					time.c			\

OBJ_FILES		= $(SRC_FILES:.c=.o)

SRCS			= $(addprefix $(SRCS_DIR)/,$(SRC_FILES))
OBJS			= $(addprefix $(OBJS_DIR)/,$(OBJ_FILES))

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
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

.PHONY: all clean fclean re
