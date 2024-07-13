SRCS = ft_split.c parsing.c builtins/cd_builtin.c builtins/pwd_builtin.c env_mani.c \
ft_itoa.c expand.c  main.c
OBJS = ${SRCS:.c=.o}
NAME = minishell
CC = cc
RM = rm -f
CFLAGS = -g -Wall -Wextra -Werror  #-fsanitize=address
LDFLAGS = -lreadline

all: ${NAME}

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${SRCS} -o ${NAME} $(LDFLAGS)

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: ${OBJS}
