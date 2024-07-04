# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/10 16:12:48 by mregrag           #+#    #+#              #
#    Updated: 2024/07/03 22:10:34 by mregrag          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT		= libft.a
LIBRAIRIE	= "lib/libft"
CC		= cc
CFLAGS		= -Wall -Wextra -Werror  -g2
HEADER		= ./include/minishell.h
RM		= rm -rf


READLINE_INC = -I$(shell brew --prefix readline)/include
READLINE_LIB = -L$(shell brew --prefix readline)/lib -lreadline

BUILTINS	:=	src/builtins/ft_cd.c \
			src/builtins/ft_echo.c \
			src/builtins/ft_env.c \
			src/builtins/ft_exit.c \
			src/builtins/ft_pwd.c \
			src/builtins/ft_unset.c \
			src/builtins/ft_export.c

ENV		:=	src/env/env_utils.c \
			src/env/init_env.c \

EXECUCTION	:=	src/execution/exe_utils.c \
			src/execution/exec_builtin.c \
			src/execution/exec_cmd.c \
			src/execution/exec_pip.c \
			src/execution/executing.c \
			src/execution/redir_utils.c \
			src/execution/redirections.c

EXPANSION	:=	src/expansion/expansion.c \
			src/expansion/handle_dolar.c \
			src/expansion/expansion_utils.c \
			src/expansion/expansion_utils1.c

PARSING		:=	src/parsing/parcing.c \
			src/parsing/parcing_utils.c

TOKENIZING	:=	src/tokens/tokinize.c \
			src/tokens/tokinize_lst.c \
			src/tokens/tokinize_utils.c \
			src/tokens/tokinize_utils1.c
UTILS		:=	src/utils/error_exit.c \
			src/utils/syntax_errors.c

MAIN		:=	src/main.c

SIGNALS		:=	src/signals/signals.c

SRCS		:=	$(BUILTINS)\
			$(EXECUCTION)\
			$(EXPANSION)\
			$(PARSING)\
			$(TOKENIZING)\
			$(SIGNALS)\
			$(UTILS)\
			$(ENV)\
			src/main.c
OBJS		:=	$(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	@make -C $(LIBRAIRIE)

# $(NAME): $(LIBFT) $(OBJS)
# 	@$(CC) -o $(NAME) $(OBJS) -L$(LIBRAIRIE) -lft -lreadline

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBRAIRIE) -lft ${READLINE_LIB}

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) ${READLINE_INC} -c $< -o $@

clean:
	@make clean -C $(LIBRAIRIE)
	@$(RM) $(OBJS)

fclean: clean
	@make fclean -C $(LIBRAIRIE)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
