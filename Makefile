# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/01 22:07:35 by lsadikaj          #+#    #+#              #
#    Updated: 2025/12/03 15:28:02 by lsadikaj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
SRCDIR	= srcs
INCDIR	= includes
OBJDIR	= objs
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
    MLX_DIR     = minilibx_mms_20200219
    MLX_LIB     = $(MLX_DIR)/libmlx.dylib
    MLX_FLAGS   = -I$(MLX_DIR)
    MLX_LINK    = -L$(MLX_DIR) -lmlx -rpath $(MLX_DIR) -framework Metal -framework MetalKit -framework Cocoa
endif

ifeq ($(UNAME_S), Linux)
    MLX_DIR     = minilibx-linux
    MLX_LIB     = $(MLX_DIR)/libmlx.a
    MLX_FLAGS   = -I$(MLX_DIR)
    MLX_LINK    = -L$(MLX_DIR) -lmlx -lXext -lX11
endif

CFLAGS      += -I$(INCDIR) $(MLX_FLAGS)
LDFLAGS     = $(MLX_LINK) -lm
SRCS        = $(SRCDIR)/main.c \
				$(SRCDIR)/init.c \
				$(SRCDIR)/hooks.c \
				$(SRCDIR)/render.c
OBJS        = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	make -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re