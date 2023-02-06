NAME = ircserv

SRC_LST = main.cpp\
		  console.cpp\
		  server.cpp\

SRC = $(addprefix $(SRC_DIR), $(SRC_LST))

INCLUDE = -I $(SRC_HDR)
CFLAGS = -Wall -Wextra -Werror -std=c++98
CC = clang++

SRC_DIR = src/
SRC_HDR	= header/
OBJ_DIR = obj/
OBJ = $(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)
DEPENDS = $(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.d)

all:	$(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) Makefile
	$(CC) $(CFLAGS) -MMD $(INCLUDE) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

-include $(DEPENDS)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp $(SRC_HDR)
	$(CC) -c $(INCLUDE) $(CFLAGS) -MMD -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean:
	rm -rf $(OBJ_DIR)
	rm -rf $(NAME)

re:	fclean all
