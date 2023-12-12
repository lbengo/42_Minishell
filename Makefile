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
EXE			:= minishell
BIN_PATH	:= ./bin
NAME		:= $(BIN_PATH)/$(EXE)
NAME_BONUS	:= $(BIN_PATH)/$(EXE)_bonus
INCLUDE		:= ./inc


CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror
LFLAGS		:= -lreadline

# Sources dir
UTILS_PATH := utils

SRC_PATH	:= src
SRC			:= main.c \
				read_input.c \
				lexer.c \
				parser.c \
				expander.c \
				$(UTILS_PATH)/is_special_char.c \
				$(UTILS_PATH)/is_special_string.c

SRC_BONUS_PATH	:= ./src_bonus
SRC_BONUS	:= main.c \
				$(UTILS_PATH)/is_special_char.c \
				$(UTILS_PATH)/is_special_string.c

LIB_PATH	:= ./lib
LIB_H		:= $(LIB_PATH)/libft.h
LIB_A		:= $(LIB_PATH)/libft.a

# Objects dir
OBJ_PATH	:= ./obj
OBJ			:= $(addprefix $(OBJ_PATH)/, $(SRC:.c=.o))

OBJ_BONUS_PATH	:= ./obj_bonus
OBJ_BONUS	:= $(addprefix $(OBJ_BONUS_PATH)/, $(SRC_BONUS:.c=.o))


########## RULES ##########
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INCLUDE) -I $(LIB_PATH) -c $^ -o $@

$(OBJ_BONUS_PATH)/%.o: $(SRC_BONUS_PATH)/%.c | $(OBJ_BONUS_PATH)
	$(CC) $(CFLAGS) -I $(INCLUDE) -I $(LIB_PATH) -c $^ -o $@

all: $(EXE)

re: fclean all

clean:
	rm -rf $(OBJ_PATH)
	rm -rf $(OBJ_BONUS_PATH)
	rm -rf *.dSYM

fclean:	clean
	rm -rf $(BIN_PATH)
	rm -rf *.out

libft: | $(LIB_PATH)
	$(MAKE) -C $(LIB_PATH)/libft fclean
	$(MAKE) -C $(LIB_PATH)/libft all
	cp $(LIB_PATH)/libft/libft.a $(LIB_A)
	cp $(LIB_PATH)/libft/libft.h $(LIB_H)


# Binaries
$(EXE): $(NAME)

$(NAME) : $(OBJ) | $(BIN_PATH)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIB_A) $(LFLAGS)

bonus: $(NAME_BONUS)

$(NAME_BONUS) : $(OBJ_BONUS) | $(BIN_PATH)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $@ $(LIB_A) $(LFLAGS)


# Debug
no_flag: CFLAGS :=
no_flag_bonus: CFLAGS :=
no_flag: $(NAME)
no_flag_bonus: $(NAME_BONUS)

debug: CFLAGS := -g3 -g -D DEBUG=1
debug_bonus: CFLAGS := -g3 -g -D DEBUG=1
debug: $(NAME)
debug_bonus: $(NAME_BONUS)

faddress: CFLAGS := -g3 -fsanitize=address
faddress_bonus: CFLAGS := -g3 -fsanitize=address
faddress: $(NAME)
faddress_bonus: $(NAME_BONUS)

# tests
run: $(NAME)
	$(NAME)


# Create dirs
$(OBJ_PATH):
	mkdir -p $@
	mkdir -p $@/$(UTILS_PATH)

$(OBJ_BONUS_PATH):
	mkdir -p $@
	mkdir -p $@/$(UTILS_PATH)

$(BIN_PATH):
	mkdir -p $@

.PHONY: clean fclean
