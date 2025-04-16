# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaterna <mmaterna@student.42warsaw.pl>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 17:37:48 by mmaterna          #+#    #+#              #
#    Updated: 2025/04/16 15:44:07 by mmaterna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= so_long
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -Iinclude

SRCS	=	so_long.c \
			map.c \
			validate_map.c \
			init.c \
			load_texture.c \
			player.c \
			check_path.c \
			draw.c \
			parse.c \
			gnl/get_next_line.c \
			gnl/get_next_line_utils.c 

OBJDIR	= obj
OBJS	= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBFTDIR = Libft
LIBFT	 = $(LIBFTDIR)/libft.a

MLX_FLAGS = -L/usr/lib -lmlx -lXext -lX11 -lm -lGL

all: $(LIBFT) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR) $(OBJDIR)/gnl

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

$(NAME): $(OBJDIR) $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $@

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all
