NAME			= philo

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
CFLAGS			+=	-pthread -g3 -fsanitize=thread
INCLUDES		=	-I./includes

SRCS_DIR		=	srcs
OBJS_DIR		=	objs
CORE_DIR		=	core
PARSING_DIR		=	parsing

SRC_FILES		=	main.c							\
            		$(CORE_DIR)/routine.c			\
            		$(CORE_DIR)/simulation.c		\
            		$(CORE_DIR)/table.c				\
            		$(CORE_DIR)/time.c				\
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

.PHONY: all clean fclean re
