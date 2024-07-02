# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 01:45:00 by mregrag           #+#    #+#              #
#    Updated: 2024/06/29 17:30:45 by mregrag          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
       ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_issamechar.c \
       ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_strjoin_char.c\
       ft_calloc.c ft_strdup.c ft_toupper.c ft_tolower.c ft_strcpy.c \
       ft_strchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_free.c \
       ft_strnstr.c ft_atoi.c ft_strrchr.c ft_substr.c ft_isquotes.c \
       ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_isspace.c \
       ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_strcmp.c \
       ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strlen_arg.c \
       ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_list_to_arrg.c \
       ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c \
       ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_strjoin_tree.c \
       ft_lstclear_bonus.c ft_lstiter_bonus.c \

OBJS	= $(SRCS:.c=.o)
NAME    = libft.a
RM	= rm -f
LIBC	= ar -rcs
FLAGS	= -Wall -Wextra -Werror
CC	= cc

all: $(NAME)

$(NAME): $(OBJS)
	@$(LIBC) $(NAME) $(OBJS)

%.o: %.c libft.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean
