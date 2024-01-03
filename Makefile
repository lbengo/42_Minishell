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
PARSER_PATH := parser


SRC_PATH	:= src
SRC			:= main.c \
				read_input.c \
				lexer.c \
				expander.c \
				exec.c \
				$(PARSER_PATH)/add_arg.c \
				$(PARSER_PATH)/add_io.c \
				$(PARSER_PATH)/add_opt.c \
				$(PARSER_PATH)/is_append.c \
				$(PARSER_PATH)/is_heredoc.c \
				$(PARSER_PATH)/parser.c \
				$(UTILS_PATH)/cmdsfree.c \
				$(UTILS_PATH)/is_special_char.c \
				$(UTILS_PATH)/is_special_string.c

SRC_BONUS_PATH	:= ./src_bonus
SRC_BONUS		:= main.c \
				$(UTILS_PATH)/is_special_char.c \
				$(UTILS_PATH)/is_special_string.c

LIB_PATH	:= ./lib
LIB_H		:= $(LIB_PATH)/libft.h
LIB_A		:= $(LIB_PATH)/libft.a

TEST					:= tests
TESTS_PARSER_PATH		:= $(TEST)/$(PARSER_PATH)
TESTS_LEXER_PATH		:= $(TEST)/lexer
TESTS_PARSER_BIN_PATH	:= $(TESTS_PARSER_PATH)/bin
TESTS_LEXER_BIN_PATH	:= $(TESTS_LEXER_PATH)/bin
TESTS_PARSER			:= $(TESTS_PARSER_PATH)/test_parser.c \
							$(TESTS_PARSER_PATH)/test_parser_1.c
TESTS_LEXER				:= $(TESTS_LEXER_PATH)/test_lexer.c
TESTS_PARSER_BIN		:= $(patsubst $(TESTS_PARSER_PATH)/%.c, \
							$(TESTS_PARSER_BIN_PATH)/%, $(TESTS_PARSER))
TESTS_LEXER_BIN			:= $(patsubst $(TESTS_LEXER_PATH)/%.c, \
							$(TESTS_LEXER_BIN_PATH)/%, $(TESTS_LEXER))
TEST_LFLAG				:= -lcriterion

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

$(TESTS_LEXER_BIN_PATH)/%: $(TESTS_LEXER_PATH)/%.c | $(TESTS_LEXER_BIN_PATH)
	$(CC) $(CFLAGS) -I $(INCLUDE) -I $(LIB_PATH) \
	$(OBJ_PATH)/lexer.o $(OBJ_PATH)/$(UTILS_PATH)/*.o \
	 $< -o $@ $(LIB_A) $(LFLAGS) $(TEST_LFLAG)

$(TESTS_PARSER_BIN_PATH)/%: $(TESTS_PARSER_PATH)/%.c | $(TESTS_PARSER_BIN_PATH)
	$(CC) $(CFLAGS) -I $(INCLUDE) -I $(LIB_PATH) \
	$(OBJ_PATH)/$(PARSER_PATH)/*.o $(OBJ_PATH)/$(UTILS_PATH)/*.o \
	 $< -o $@ $(LIB_A) $(LFLAGS) $(TEST_LFLAG)

all: $(EXE)

re: fclean all

clean:
	rm -rf $(OBJ_PATH)
	rm -rf $(OBJ_BONUS_PATH)
	rm -rf $(TESTS_LEXER_PATH)/bin
	rm -rf $(TESTS_PARSER_PATH)/bin
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

fstrict: CFLAGS += -g3 -fsanitize=address
fstrict: $(NAME)

# tests
test_lexer: $(OBJ) $(TESTS_LEXER_BIN)
	for test in $(TESTS_LEXER_BIN) ; do ./$$test ; done

test_parser: $(OBJ) $(TESTS_PARSER_BIN)
	for test in $(TESTS_PARSER_BIN) ; do ./$$test > /dev/null ; done

run: $(NAME)
	$(NAME)


# Create dirs
$(OBJ_PATH):
	mkdir -p $@
	mkdir -p $@/$(UTILS_PATH)
	mkdir -p $@/$(PARSER_PATH)

$(OBJ_BONUS_PATH):
	mkdir -p $@
	mkdir -p $@/$(UTILS_PATH)
	mkdir -p $@/$(PARSER_PATH)

$(BIN_PATH):
	mkdir -p $@

$(TESTS_LEXER_BIN_PATH):
	mkdir -p $@

$(TESTS_PARSER_BIN_PATH):
	mkdir -p $@


.PHONY: clean fclean
