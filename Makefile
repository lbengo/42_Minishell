# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daampuru <daampuru@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/08 21:21:51 by daampuru          #+#    #+#              #
#    Updated: 2023/12/08 21:21:51 by daampuru         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########## VARIABLES ##########
BIN_PATH	:= ./bin
NAME		:= $(BIN_PATH)/minishell
NAME_BONUS	:= $(BIN_PATH)/minishell_bonus
INCLUDE		:= ./inc
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -lreadline

# Sources dir
SUB_PATH := statemachine

SRC_PATH	:= src
SRC			:= main.c \
				$(SUB_PATH)/thinking.c

SRC_BONUS_PATH	:= ./src_bonus
SRC_BONUS	:= main.c \
				$(SUB_PATH)/thinking.c

# Objects dir
OBJ_PATH	:= ./obj
OBJ			:= $(addprefix $(OBJ_PATH)/, $(SRC:.c=.o))

OBJ_BONUS_PATH	:= ./obj_bonus
OBJ_BONUS	:= $(addprefix $(OBJ_BONUS_PATH)/, $(SRC_BONUS:.c=.o))


########## RULES ##########
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $^ -o $@

$(OBJ_BONUS_PATH)/%.o: $(SRC_BONUS_PATH)/%.c | $(OBJ_BONUS_PATH)
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $^ -o $@

all: philo

re: fclean all

clean:
	rm -rf $(OBJ_PATH)
	rm -rf $(OBJ_BONUS_PATH)
	rm -rf *.dSYM

fclean:	clean
	rm -rf $(BIN_PATH)
	rm -rf *.out


# Binaries
minishell: $(NAME)

$(NAME) : $(OBJ) | $(BIN_PATH)
	$(CC) $(CFLAGS) $(OBJ) -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS) : $(OBJ_BONUS) | $(BIN_PATH)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $@


# Debug
no_flag: CFLAGS := -lreadline
no_flag_bonus: CFLAGS := -lreadline
no_flag: $(NAME)
no_flag_bonus: $(NAME_BONUS)

debug: CFLAGS := -g3 -g -D DEBUG=1 -lreadline
debug_bonus: CFLAGS := -g3 -g -D DEBUG=1 -lreadline
debug: $(NAME)
debug_bonus: $(NAME_BONUS)

faddress: CFLAGS := -g3 -fsanitize=address -lreadline
faddress_bonus: CFLAGS := -g3 -fsanitize=address -lreadline
faddress: $(NAME)
faddress_bonus: $(NAME_BONUS)

# tests
run: $(NAME)
	$(NAME)


# Create dirs
$(OBJ_PATH):
	mkdir -p $@
	mkdir -p $@/$(SUB_PATH)

$(OBJ_BONUS_PATH):
	mkdir -p $@
	mkdir -p $@/$(SUB_PATH)

$(BIN_PATH):
	mkdir -p $@

.PHONY: clean fclean
