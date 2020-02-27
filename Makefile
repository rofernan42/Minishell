# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/12 15:44:33 by rofernan          #+#    #+#              #
#    Updated: 2020/02/27 13:44:51 by rofernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				=	minishell

SRCS_PATH			=	./srcs/
INC_PATH			=	./includes/
OBJS_PATH			=	./objs/

SRCS_NAME			=	builtin.c \
						check_quotes.c \
						conditions.c \
						copy_close_fd.c \
						create_env.c \
						env_addback.c \
						env_clear.c \
						env_delone.c \
						env_find.c \
						env_new.c \
						error.c \
						extract.c \
						forks.c \
						free.c \
						ft_cd.c \
						ft_echo.c \
						ft_env.c \
						ft_exit.c \
						ft_export.c \
						ft_pwd.c \
						ft_stdin.c \
						ft_unset.c \
						init_table.c \
						init.c \
						main.c \
						path.c \
						pop_word.c \
						redirection.c \
						replace.c \
						rev_cmd.c \
						shell_body.c \
						split.c \
						status_res.c \
						tabs.c \
						translate.c \
						utils_2.c \
						utils.c \
						wrap_cmp.c \
						wrap_parsing.c

INC_NAME			=	mini_struct.h \
						minishell.h

OBJS_NAME			=	$(SRCS_NAME:.c=.o)

OBJS				=	$(addprefix $(OBJS_PATH), $(OBJS_NAME))
INC					=	$(addprefix $(INC_PATH), $(INC_NAME))

CC					=	gcc

CFLAGS				=	-Wall -Wextra -Werror -I./
LIB					=	./libft/libft.a

all:					$(NAME)

$(NAME):				$(OBJS)
						@(make -C ./libft/)
						$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)
						@(echo "\033[32m=== COMPILATION MINISHELL OK ===\033[0m")

$(OBJS_PATH)%.o:		$(SRCS_PATH)%.c
						@mkdir $(OBJS_PATH) 2> /dev/null || true
						@($(CC) $(CFLAGS) -o $@ -c $<)

clean:
						@(make clean -C ./libft/)
						rm -rf $(OBJS)

fclean:
						@(rm -rf $(OBJS_PATH) $(NAME))
						@echo "\033[34m=== REPERTORY MINISHELL CLEANED ===\033[0m"
						@(make fclean -C ./libft/)

re:						fclean all

.PHONY:					clean fclean re all bonus

.SILENT: