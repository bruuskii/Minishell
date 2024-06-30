SRCS = ft_split.c main.c
OBJS = ${SRCS:.c=.o}
NAME = minishell
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
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
