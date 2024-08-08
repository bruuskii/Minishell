# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/23 16:03:48 by ainouni           #+#    #+#              #
#    Updated: 2024/08/08 13:48:09 by ainouni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
 ft_isprint.c ft_strlen.c ft_toupper.c ft_tolower.c ft_memset.c \
 ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
 ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strchr.c ft_memchr.c \
 ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
 ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
 ft_strmapi.c  ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
 ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c ft_isblanks.c \

OFILES = ${CFILES:.c=.o}
CFLAGS = -Wall -Wextra -Werror
CC = cc 

NAME = libft.a

all: $(NAME)

${NAME} : ${OFILES}
	@ar rc ${NAME} ${OFILES}

clean:
	@rm -f ${OFILES}

fclean:
	@rm -rf $(NAME)
	@rm -rf ${OFILES}

re: fclean all

.PHONY:OFILES
	 all fclean clean re make
