# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiarcer <jiarcer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/01 22:07:35 by lsadikaj          #+#    #+#              #
#    Updated: 2026/01/22 13:04:47 by jiarcer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g3 -O0
SRCDIR	= srcs
INCDIR	= includes
OBJDIR	= objs
UNAME_S := $(shell uname -s)

LIBFT_DIR  = libft
LIBFT_LIB  = $(LIBFT_DIR)/libft.a

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

CFLAGS      += -I$(INCDIR) $(MLX_FLAGS) -I$(LIBFT_DIR)
LDFLAGS     = $(MLX_LINK) -L$(LIBFT_DIR) -lft -lm
SRCS        = $(SRCDIR)/main.c \
				$(SRCDIR)/checker/checkers.c \
				$(SRCDIR)/checker/checkers2.c \
				$(SRCDIR)/checker/check_aclnb.c \
				$(SRCDIR)/checker/check_args.c \
				$(SRCDIR)/checker/read_args.c \
				$(SRCDIR)/parser/parse_ambient.c \
				$(SRCDIR)/parser/parse_sphere.c \
				$(SRCDIR)/parser/parse_plan.c \
				$(SRCDIR)/parser/parse_cylinder.c \
				$(SRCDIR)/parser/parse_all.c \
				$(SRCDIR)/parser/parser_utils.c \
				$(SRCDIR)/parser/parse_acl.c \
				$(SRCDIR)/raytracer/render.c \
				$(SRCDIR)/raytracer/generate_ray.c \
				$(SRCDIR)/raytracer/find_calcul_val.c \
				$(SRCDIR)/raytracer/ray_cylinder.c \
				$(SRCDIR)/raytracer/ray_plane.c \
				$(SRCDIR)/raytracer/ray_sphere.c \
				$(SRCDIR)/raytracer/intersect_cylinder.c \
				$(SRCDIR)/utils/init.c \
				$(SRCDIR)/utils/hooks.c \
				$(SRCDIR)/utils/clean.c \
				$(SRCDIR)/utils/utils.c \
				$(SRCDIR)/utils/vec_utils.c


OBJS        = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(LIBFT_LIB) $(MLX_LIB) $(NAME)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

$(MLX_LIB):
	make -C $(MLX_DIR)
	cp minilibx_mms_20200219/libmlx.dylib .

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	@make -C $(LIBFT_DIR) clean || true

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean || true

re: fclean all

.PHONY: all clean fclean re