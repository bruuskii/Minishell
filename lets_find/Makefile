SRCS = parsing.c builtins/cd_builtin.c builtins/pwd_builtin.c env_mani.c \
	   main.c builtins/export.c execute.c expand.c command_to_execution.c f_split.c \
	   first_parse.c

OBJS = ${SRCS:.c=.o}
NAME = minishell
CC = cc
LIBFT_DIR = Libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
RM = rm -f
CFLAGS = -g -Wall -Wextra -Werror  #-fsanitize=address
LDFLAGS = -lreadline

all: ${NAME}

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

${NAME}:  ${OBJS} $(LIBFT_LIB)
	@${CC} ${CFLAGS} ${SRCS} -o ${NAME} $(LIBFT_LIB)  $(LDFLAGS)

clean:
	@${RM} ${OBJS}
	make -C $(LIBFT_DIR) clean

fclean: clean
	@${RM} ${NAME}
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: ${OBJS}
