# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaterna <mmaterna@student.42warsaw.pl>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/19 17:38:07 by mmaterna          #+#    #+#              #
#    Updated: 2025/04/08 17:09:24 by mmaterna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the library file
NAME = libft.a

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Path to source files
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
      ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
      ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
      ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
      ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
      ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_substr.c

# Printf source files
PRINTF_SRCS = ft_printf.c ft_convert_hex.c ft_utilis.c

# All sources combined
ALL_SRCS = $(SRCS) $(PRINTF_SRCS)

# Object files
OBJS = $(SRCS:.c=.o)
PRINTF_OBJS = $(PRINTF_SRCS:.c=.o)
ALL_OBJS = $(OBJS) $(PRINTF_OBJS)

# Default rule
all: $(NAME)

# Creating the libft.a library
$(NAME): $(ALL_OBJS)
	ar rcs $@ $^

# Compiling libft .c files into .o files
$(OBJS): %.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compiling printf .c files into .o files
$(PRINTF_OBJS): %.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

# Deleting object files and the library
clean:
	rm -f $(ALL_OBJS)

# Deleting object files and the library and preparing for a fresh compilation
fclean: clean
	rm -f $(NAME)

# Cleaning and recompiling
re: fclean all

.PHONY: all clean fclean re
