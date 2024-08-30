SRCS = parsing.c builtins/cd_builtin.c builtins/pwd_builtin.c env_mani.c \
       main.c builtins/export.c  expand.c command_to_execution.c f_split.c \
       first_parse.c  execution/get_path.c execution/execute_utils1.c execution/herdoc.c \
       execution/execute.c  builtins/unset.c builtins/echo.c execution/ft_free.c  \
       builtins/ft_exit.c execution/input_output.c execution/execute_utils.c \
       execution/execute_utils00.c execution/herdoc_utils.c execution/ft_free_utils.c \
       builtins/ft_export.c builtins/ft_export_utils.c  commad_to_execution_utils.c command_to_execution_file.c \
       command_to_execution_parse.c env_mani_pwd.c env_mani_utils.c expand_dollar.c expand_helpers.c expand_process.c expand_special.c f_split_count.c \
       f_split_handlers.c f_split_process.c f_split_utils.c parsing_grep.c parsing_helpers.c parsing_utils.c parsing_quotes.c  commad_to_execution_token.c \
	   parsing_is.c

OBJS = ${SRCS:.c=.o}
NAME = minishell
CC = cc
LIBFT_DIR = Libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
RM = rm -f
CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address
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
