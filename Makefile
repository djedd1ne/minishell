# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 00:30:57 by mokoucha          #+#    #+#              #
#    Updated: 2023/02/28 02:31:57 by mokoucha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -L /Users/$(USER)/.brew/opt/readline/lib -lreadline -I /Users/$(USER)/.brew/opt/readline/include

NAME = minishell

LIBFT = libft/libft.a

SRC = parser/parser.c\
	parser/parser_util.c\
	builtins/cd.c\
	builtins/echo.c\
	builtins/env.c\
	builtins/env_utils.c\
	builtins/exit.c\
	builtins/export.c\
	builtins/export_utils.c\
	builtins/pwd.c\
	builtins/unset.c\
	shell_core/executor.c\
	shell_core/executor_utils.c\
	shell_core/main.c\
	shell_core/executor_utils2.c\
	shell_core/executor_utils3.c\
	tokenizer/tokenizer.c\
	tokenizer/tokenizer_utils.c\
	tokenizer/tokenizer_utils2.c\
	tokenizer/tokenizer_utils3.c\
	tokenizer/shell_expansion.c\
	tokenizer/lex.c\
	utils/error.c\
	utils/signal_utils.c\
	utils/utils.c\
	utils/utils2.c\
	utils/utils3.c\

OBJ = $(SRC:.c=.o)

%.o : %.c
	@${CC} $(INCLUDE) ${CFLAG} -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) 
	@make -C libft
	@$(CC)  -o $(NAME) $(OBJ) libft/libft.a $(CFLAGS)
	@echo "$(NAME) created"

$(LIBFT) : 
	@make -C libft

clean:
	@make clean -C libft
	@rm -f $(OBJ)
	@echo "$(NAME) objects deleted"

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "$(NAME) deleted"

re: fclean all
