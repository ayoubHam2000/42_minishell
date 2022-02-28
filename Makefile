# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/22 09:30:37 by aben-ham          #+#    #+#              #
#    Updated: 2022/02/28 13:14:50 by aben-ham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UTIL_FILES = \
	utils/ft_atoi.c \
	utils/ft_memchr.c \
	utils/ft_memcmp.c \
	utils/ft_memcpy.c \
	utils/ft_memmove.c \
	utils/ft_memset.c \
	utils/ft_putstr.c \
	utils/ft_putstr_fd.c \
	utils/ft_split.c \
	utils/ft_strchr.c \
	utils/ft_strdup.c \
	utils/ft_strjoin.c \
	utils/ft_strlcpy.c \
	utils/ft_strlen.c \
	utils/ft_strncmp.c \
	utils/ft_strnstr.c \
	utils/ft_strrchr.c \
	utils/ft_substr.c \
	utils/ft_error.c \
	utils/ft_error_exit.c \
	utils/queue_c/q_clear.c \
	utils/queue_c/q_clone.c \
	utils/queue_c/q_dequeue.c \
	utils/queue_c/q_enqueue.c \
	utils/queue_c/q_init.c

COMMANDS_FILES = \

FILES = \
	$(UTIL_FILES) \
	$(COMMANDS_FILES) \
	src/signals.c \
	parser/parser.c \
	parser/expansion.c \
	main.c

#ls -d [dir/*] | grep "" | sed 's/$/ \\/g'
#-Wall -Wextra -Werror
CFLAGS = -g -I includes/
#FLAGS = -lreadline -L ~/brew/opt/readline/lib  -I ~/brew/opt/readline/include
DEPFLAGS = -MMD -MF $(@:.o=.d)

NAME = minishell

OBJ_DIR = _OUT/

OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

deps = $(OBJ:.o=.d)

all : $(NAME)

$(NAME) : $(OBJ)
	gcc $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ) : $(OBJ_DIR)%.o : %.c
	mkdir -p $(dir $@)
	gcc $(CFLAGS) -c $(@:_OUT/%.o=%.c) $(DEPFLAGS) -o $@

-include $(deps)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all
#~/goinfre/brew/opt/readline/lib/libreadline.a .
#~/goinfre/brew/opt/readline/lib/libhistory.a .
