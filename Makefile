# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 13:50:32 by rteles-f          #+#    #+#              #
#    Updated: 2023/09/17 00:29:10 by rteles-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

COLOR_RESET =	\033[0m
COLOR_GREEN =	\033[32m

NAME		= 	minishell

CC			= 	cc -g #-fsanitize=address 

CFLAGS		= 	-Wall -Wextra -Werror $(INCLUDES)

LIBFLAGS	=	-lreadline -ltermcap -lncurses

RM			= 	rm -f

INCLUDES	= 	-Iheaders/ -Isrc/libft/libft_includes

SRCS		=	src/builtins/and_or_all.c src/builtins/builtin_utils.c src/builtins/cd.c src/builtins/echo.c \
				src/builtins/env.c src/builtins/exit.c src/builtins/expansion.c src/builtins/export.c \
				src/builtins/export_utils.c src/builtins/input_redirect.c src/builtins/input_utils.c \
				src/builtins/output_redirect.c src/builtins/pwd.c src/builtins/quotes.c src/builtins/unset.c \
				src/builtins/wildcard.c src/builtins/wildcard_utils2.c src/builtins/wildcard_utils.c \
\
				src/libft/ft_atoi.c src/libft/ft_bzero.c src/libft/ft_calloc.c src/libft/ft_isalnum.c \
				src/libft/ft_isalpha.c src/libft/ft_isascii.c src/libft/ft_isdigit.c src/libft/ft_isprint.c \
				src/libft/ft_itoa.c src/libft/ft_lstadd_back.c src/libft/ft_lstadd_front.c src/libft/ft_lstclear.c \
				src/libft/ft_lstdelone.c src/libft/ft_lstiter.c src/libft/ft_lstlast.c src/libft/ft_lstmap.c \
				src/libft/ft_lstnew.c src/libft/ft_lstsize.c src/libft/ft_memchr.c src/libft/ft_memcmp.c \
				src/libft/ft_memcpy.c src/libft/ft_memmove.c src/libft/ft_memset.c src/libft/ft_putchar_fd.c \
				src/libft/ft_putendl_fd.c src/libft/ft_putnbr_fd.c src/libft/ft_putstr_fd.c src/libft/ft_split.c \
				src/libft/ft_strchr.c src/libft/ft_strcmp.c src/libft/ft_strdup.c src/libft/ft_striteri.c \
				src/libft/ft_strjoin.c src/libft/ft_strlcat.c src/libft/ft_strlcpy.c src/libft/ft_strlen.c \
				src/libft/ft_strmapi.c src/libft/ft_strncmp.c src/libft/ft_strnstr.c src/libft/ft_strrchr.c \
				src/libft/ft_strtrim.c src/libft/ft_substr.c src/libft/ft_tolower.c src/libft/ft_toupper.c \
\
				src/main/0.setup.c src/main/1.main.c src/main/2.parse.c src/main/3.normalize.c src/main/4.commands.c \
				src/main/5.execution.c src/main/6.reset.c src/main/commands_utils.c src/main/execution_utils.c \
				src/main/normalize_utils.c src/main/parse_utils.c src/main/setup_utils.c \
\
				src/utils/libft_plus2.c src/utils/libft_plus.c src/utils/shell_split.c src/utils/shell_split_utils.c \
				src/utils/temp_utils.c	src/utils/temp_utils2.c	src/utils/parse_utils2.c src/builtins/here_doc.c

OBJS		= 	$(SRCS:.c=.o)

all: 		$(NAME)

$(NAME):	$(OBJS)
			@make bonus -s -C src/libft
			@$(CC) $(CFLAGS) $(OBJS) src/libft/libft.a -o $(NAME) $(LIBFLAGS)
			@echo "[$(COLOR_GREEN)info$(COLOR_RESET)]: Minishell Built"

clean:
			@make clean -s -C src/libft
			@$(RM) $(OBJS)
			@echo "[$(COLOR_GREEN)info$(COLOR_RESET)]: Clean"

fclean: 	clean
			@make fclean -s -C src/libft
			@$(RM) $(NAME)
			@echo "[$(COLOR_GREEN)info$(COLOR_RESET)]: Full"

re:			fclean all

norm :
			@norminette -R CheckForbiddenSourceHeader $(SRCS) headers/

r:
			@make && clear && ./$(NAME)

v:
			make re && clear && valgrind -s --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=.ignore_readline --trace-children=yes ./minishell


.PHONY: 	all re clean fclean
