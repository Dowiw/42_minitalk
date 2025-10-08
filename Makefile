# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/08 20:19:17 by kmonjard          #+#    #+#              #
#    Updated: 2025/10/08 20:19:18 by kmonjard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server

CC_FLAGS = -Wall -Werror -Wextra
CC = gcc

SRC_DIR = ./src/
LIBFT = $(SRC_DIR)/libft/libft.a

CLIENT_C = client.c
SERVER_C = server.c

CLIENT_SRC = $(addprefix $(SRC_DIR), $(CLIENT_C))
SERVER_SRC = $(addprefix $(SRC_DIR), $(SERVER_C))

CLIENT_O = $(CLIENT_SRC:.c=.o)
SERVER_O = $(SERVER_SRC:.c=.o)

INCLUDES = ./headers

# -- Rules --
all: $(LIBFT) $(NAME_CLIENT) $(NAME_SERVER)

$(LIBFT):
	make -C $(SRC_DIR)/libft/

$(NAME_CLIENT): $(CLIENT_O)
	@$(CC) $(CC_FLAGS) $(CLIENT_O) $(LIBFT) -o $(NAME_CLIENT)

$(NAME_SERVER): $(SERVER_O)
	@$(CC) $(CC_FLAGS) $(SERVER_O) $(LIBFT) -o $(NAME_SERVER)

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CC_FLAGS) -c $< -o $@ -I$(INCLUDES)

clean:
	@make -C ./src/libft clean
	@echo "Deleting object files in minitalk..."
	@rm -f $(CLIENT_O) $(SERVER_O)

fclean:
	@make -C ./src/libft fclean
	@echo "Deleting object files in fdf..."
	@echo "Deleting all binaries in fdf..."
	@rm -f $(NAME_CLIENT) $(NAME_SERVER)
	@rm -f $(CLIENT_O) $(SERVER_O)

re: fclean all

.PHONY: all clean fclean re
