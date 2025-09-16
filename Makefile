# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/22 10:03:05 by erico-ke          #+#    #+#              #
#    Updated: 2025/05/29 20:31:42 by erico-ke         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CC := gcc

CFLAGS := -Wall -Werror -Wextra -g

RLINE := -lreadline

SANITIZE := sanitize
SANITIZE_MEM := sanitize_mem

FSANITIZE:= -fsanitize=thread -g3
FSANITIZE_MEM := -fsanitize=address -g

INCLUDES = -Iincludes/ -Ilibft/includes
OBJDIR := obj

LIBFT = libft/libft.a

MAIN ?= main.c

COMMON_SRC = src/built-ins/cd.c src/built-ins/echo.c src/built-ins/env.c src/built-ins/exit.c \
		src/built-ins/export.c src/built-ins/pwd.c src/built-ins/unset.c \
		src/exec/exec.c src/exec/pipes.c src/exec/redir.c src/exec/signals.c \
		src/parsing/parsing.c src/parsing/parsing2.c src/parsing/varcheck.c \
		src/tokens/tokens.c src/tokens/tokens2.c \
		src/utils/builtins_utils.c src/utils/echo_utils.c src/utils/exec_utils.c \
		src/utils/here_doc_utils.c src/utils/map_utils.c src/utils/map_utils2.c \
		src/utils/map_utils3.c src/utils/redir_utils.c src/utils/redir_utils2.c \
		src/utils/structs_init.c src/utils/structs_init2.c src/utils/token_utils.c \
		src/utils/pipes_utils.c src/utils/utils.c \
		src/validations/validations.c \
		src/exec/expandable.c \

SRC = $(COMMON_SRC) $(MAIN)

all : $(NAME)

$(LIBFT) :
	@make -s -C libft
	@echo "$(GREEN)LIBFT COMPILED$(DEF_COLOR)"

OBJ = $(patsubst src/%.c, $(OBJDIR)/%.o, $(SRC))

$(OBJDIR)/%.o : src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME) : $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -o $(NAME) $(RLINE)
	@echo "$(GREEN)MINISHELL COMPILED with MAIN=$(MAIN)$(DEF_COLOR)"

clean :
	@echo "$(YELLOW)Deleting all object files....$(DEF_COLOR)"
	@rm -rf $(OBJDIR)
	@make -s -C libft clean
	@echo "$(RED)All object files were deleteated...$(DEF_COLOR)"

fclean : clean
	@echo "$(YELLOW)Deleting executable files....$(DEF_COLOR)"
	@rm -f $(NAME)
	@make -s -C libft fclean
	@echo "$(RED)All executable files has been deleted.$(DEF_COLOR)"

re : fclean all

norm :
	@echo "$(CYAN)Norminette src/$(GREEN)"
	@norminette src/
	@echo "$(CYAN)Norminette includes/$(GREEN)"
	@norminette includes/
	@echo "$(DEF_COLOR)"

$(SANITIZE) : $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDES) $(FSANITIZE) $(OBJ) $(LIBFT) -o $(NAME) $(RLINE)
	@echo "$(CYAN)Compiling minishell with fsanitize$(DEF_COLOR)"


$(SANITIZE_MEM) : $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDES) $(FSANITIZE_MEM) $(OBJ) $(LIBFT) -o $(NAME) $(RLINE)
	@echo "$(CYAN)Compiling minishell with fsanitize ADDRESS$(DEF_COLOR)"
# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m