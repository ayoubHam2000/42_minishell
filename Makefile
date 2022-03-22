# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/22 09:30:37 by aben-ham          #+#    #+#              #
#    Updated: 2022/03/22 21:32:23 by aben-ham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UTIL_FILES = \
	utils/ft_arrlen.c \
	utils/ft_isalnum.c \
	utils/ft_isalpha.c \
	utils/ft_substr.c \
	utils/ft_atoi.c \
	utils/ft_memchr.c \
	utils/ft_memcmp.c \
	utils/ft_memcpy.c \
	utils/ft_memmove.c \
	utils/ft_memset.c \
	utils/ft_putstr.c \
	utils/ft_putstr_fd.c \
	utils/ft_split.c \
	utils/ft_isdigit.c \
	utils/msk_split.c \
	utils/ft_strchr.c \
	utils/ft_strdup.c \
	utils/ft_strjoin.c \
	utils/ft_strlcpy.c \
	utils/ft_strlen.c \
	utils/ft_strncmp.c \
	utils/ft_strnstr.c \
	utils/ft_strrchr.c \
	utils/ft_error.c \
	utils/ft_error_exit.c \
	utils/ft_malloc.c \
	utils/ft_strcmp.c \
	utils/queue_c/q_clear.c \
	utils/queue_c/q_dequeue.c \
	utils/queue_c/q_enqueue.c \
	utils/queue_c/q_init.c \
	utils/ft_itoa.c \
	utils/file_error.c

EXECUTION_FILES = \
	execution/builtin/cd.c \
	execution/builtin/echo.c \
	execution/builtin/exit.c \
	execution/builtin/export.c \
	execution/builtin/pwd.c \
	execution/builtin/unset.c \
	execution/builtin/ft_env.c \
	execution/pipe/pipe.c \
	execution/set_exit_status.c \
	execution/execute.c

PARSING_FILES = \
	parser/parser.c \
	parser/expansion.c \
	parser/check_sysntax.c \
	parser/get_structure.c \
	parser/expand.c \
	parser/ft_getenv.c \
	parser/redirection_type.c \
	parser/io_files/close_files.c \
	parser/io_files/open_files_utils.c \
	parser/io_files/open_files.c

FILES = \
	$(UTIL_FILES) \
	$(EXECUTION_FILES) \
	$(PARSING_FILES) \
	src/signals.c \
	other.c \
	main.c

#-Wall -Wextra -Werror
CFLAGS = -g -I includes/
FLAGS = -lreadline -L ~/brew/opt/readline/lib  -I ~/brew/opt/readline/include  
# -fsanitize=address
#FLAGS = -lreadline 
DEPFLAGS = -MMD -MF $(@:.o=.d)

NAME = minishell

OBJ_DIR = _OUT/

OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

deps = $(OBJ:.o=.d)

all : $(NAME)

$(NAME) : $(OBJ)
	gcc  $(OBJ) $(FLAGS) -o $(NAME)

$(OBJ) : $(OBJ_DIR)%.o : %.c
	mkdir -p $(dir $@)
	gcc $(CFLAGS) -c $(@:_OUT/%.o=%.c) $(DEPFLAGS) -o $@

-include $(deps)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all
