FILES = \
	main.c

#-Wall -Wextra -Werror
CFLAGS = -I includes/
FLAGS = -lreadline 
DEPFLAGS = -MMD -MF $(@:.o=.d)

NAME = minishell

OBJ_DIR = OUT/

OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

deps = $(OBJ:.o=.d)

all : $(NAME)

$(NAME) : $(OBJ)
	gcc $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ) : $(OBJ_DIR)%.o : %.c
	mkdir -p $(dir $@)
	gcc $(CFLAGS) -c $(@:OUT/%.o=%.c) $(DEPFLAGS) -o $@

-include $(deps)
