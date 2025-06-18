# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/16 15:36:12 by jtoumani          #+#    #+#              #
#    Updated: 2025/06/18 12:43:15 by jtoumani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror


NAME_CLIENT = client
NAME_SERVER = server


LIBFT_DIR = Libft
PRINTF_DIR = Printf


LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a


INCLUDES = -I$(LIBFT_DIR) -I$(PRINTF_DIR)


CLIENT_SRC = client.c
SERVER_SRC = server.c


CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)


all: $(LIBFT) $(PRINTF) $(NAME_CLIENT) $(NAME_SERVER)


$(NAME_CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(CLIENT_OBJ) $(LIBFT) $(PRINTF) $(INCLUDES)


$(NAME_SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(SERVER_OBJ) $(LIBFT) $(PRINTF) $(INCLUDES)


$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)


%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


clean:
	rm -f *.o
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(PRINTF_DIR)

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re
