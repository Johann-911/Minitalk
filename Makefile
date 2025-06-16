# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/16 15:36:12 by jtoumani          #+#    #+#              #
#    Updated: 2025/06/16 16:58:14 by jtoumani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

LIBFT_DIR = Libft
PRINTF_DIR = Printf

LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a

SRC_FILES = client.c \
			server.c

OBJS = $(SRC_FILES:.c=.o)

INCLUDES = -I$(LIBFT_DIR) -I$(PRINTF_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -libftprintf

$(LIBFT):
	make -C $(LIBFT_DIR)

$(PRINTF):
	make -C $(PRINTF_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(PRINTF_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re