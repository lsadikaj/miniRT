# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 09:40:46 by lsadikaj          #+#    #+#              #
#    Updated: 2024/12/26 12:42:59 by lsadikaj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line
BONUS_NAME = get_next_line_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -I ../libft =-I libft

SRCS = get_next_line.c
OBJS = $(SRCS:.c=.o)

BONUS_SRCS = get_next_line_bonus.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(OBJS)

bonus: $(BONUS_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean : clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all