# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/10 16:12:48 by mregrag           #+#    #+#              #
#    Updated: 2024/08/07 00:44:28 by mregrag          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT		= libft.a
LIBRAIRIE	= "lib/libft"
FSS		=
CC		= cc
CFLAGS		= -Wall -Wextra -Werror
HEADER		= ./include/minishell.h
HEADERLIBFT	= ./lib/libft/libft.h
RM		= rm -rf
READLINE_INC 	= -I$(shell brew --prefix readline)/include
READLINE_LIB	= -L$(shell brew --prefix readline)/lib -lreadline

BUILTINS	:=	src/builtins/ft_cd.c \
			src/builtins/ft_echo.c \
			src/builtins/ft_env.c \
			src/builtins/ft_exit.c \
			src/builtins/ft_pwd.c \
			src/builtins/ft_unset.c \
			src/builtins/ft_export.c

ENV		:=	src/env/env_utils.c \
			src/env/init_env.c \
			src/env/utils.c

EXECUTION	:=	src/execution/execute_builtin.c \
			src/execution/execute_command.c \
			src/execution/execute_pip.c \
			src/execution/executing.c \
			src/execution/redirections.c \
			src/execution/redire_utils.c \
			src/execution/heredoc.c

EXPANSION	:=	src/expansion/expansion.c \
			src/expansion/handle_dolar.c \
			src/expansion/expansion_utils.c \
			src/expansion/expansion_utils1.c \

PARSING		:=	src/parsing/parcing_tokens.c \
			src/parsing/parcing_utils.c

TOKENIZING	:=	src/tokens/tokinize.c \
			src/tokens/tokinize_lst.c \
			src/tokens/tokinize_utils.c \
			src/tokens/tokinize_utils1.c

UTILS		:=	src/utils/error_exit.c \
			src/utils/syntax_errors.c\
			src/utils/system_utils.c

MAIN		:=	src/main.c

SIGNALS		:=	src/signals/signals1.c \
			src/signals/signals2.c

SRCS		:=	$(BUILTINS)\
			$(EXECUTION)\
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

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME) -L$(LIBRAIRIE) -lft -lreadline $(READLINE_LIB)

%.o: %.c $(HEADER) $(HEADERLIBFT)
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean:
	@make clean -C $(LIBRAIRIE)
	@$(RM) $(OBJS)

fclean: clean
	@make fclean -C $(LIBRAIRIE)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
