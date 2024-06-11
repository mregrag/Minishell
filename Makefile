# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/10 16:12:48 by mregrag           #+#    #+#              #
#    Updated: 2024/06/11 18:52:50 by mregrag          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
FSS = fsanitize=address -fno-omit-frame-pointer -g2
FALGS = -Wall -Wextra -Werror
HEADER = ./include/minishell.h
RM = rm -rf

SRCS_DIR = src/
OBJ_DIR = obj/

SRC = src/main \
      src/utils/libft/ft_atoi \
      src/utils/libft/ft_lstadd_back \
      src/utils/libft/ft_lstadd_front \
      src/utils/libft/ft_strdup \
      src/utils/libft/ft_strjoin \
      src/utils/libft/ft_memcmp \
      src/utils/libft/ft_strlen \
      src/utils/libft/ft_strtrim \
      src/utils/libft/ft_strchr \
      src/utils/libft/ft_strlcpy \
      src/utils/libft/ft_strcmp \
      src/utils/libft/ft_strncmp \
      src/utils/libft/ft_substr \
      src/utils/libft/ft_putstr_fd \
      src/utils/libft/ft_putchar_fd \
      src/utils/libft/ft_isspace \
      src/utils/libft/ft_splite \
      src/utils/libft/ft_calloc \
      src/utils/libft/ft_isdigit \
      src/utils/libft/ft_isalnum \
      src/utils/libft/ft_isalpha \
      src/utils/libft/ft_strjoin_f \
      src/utils/libft/ft_free_matrix \
      src/utils/libft/ft_lstsize \
      src/utils/libft/ft_itoa \
      src/utils/libft/ft_isdollar \
      src/utils/libft/ft_isquotes \
      src/utils/libft/ft_issamechar \
      src/utils/libft/ft_isoddeven_char \
      src/utils/libft/ft_bzero \
      src/utils/libft/ft_memset \
      src/utils/libft/ft_lstclear \
      src/utils/libft/ft_lstnew \
      src/utils/libft/ft_list_to_arr \
      src/utils/libft/ft_strlen_arg \
      src/parsing/parcing \
      src/tokens/tokinize \
      src/tokens/tokinize_lst \
      src/tokens/tokinize_utils \
      src/tokens/tokinize_utils1 \
      src/parsing/parcing_utils \
      src/env/env_utils \
      src/env/env_init \
      src/execution/executing \
      src/execution/exec_builtin \
      src/execution/exec_pip \
      src/execution/exec_cmd \
      src/execution/redirections \
      src/execution/redir_utils \
      src/utils/error_exit \
      src/expend/remov_quets \
      src/expend/expanding \
      src/expend/expand_utils \
      src/expend/clean_empty_string \
      src/bultin/ft_echo \
      src/bultin/ft_env \
      src/bultin/ft_pwd \
      src/bultin/ft_cd \
      src/bultin/ft_exit \
      src/bultin/ft_unset \
      src/bultin/ft_export \
      src/signals/signals \


SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

all: ${NAME}

${NAME}: ${OBJS} ${HEADER}
	@${CC} ${FALGS} ${OBJS} -o $@ -lreadline

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p ${@D}
	${CC} ${FALGS} -c $< -o $@

clean:
	@${RM} ${OBJ_DIR}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY = all clean fclean re

