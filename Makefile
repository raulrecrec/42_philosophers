# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/25 16:25:10 by rexposit          #+#    #+#              #
#    Updated: 2025/09/25 16:35:41 by rexposit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del ejecutable
NAME = philo

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Archivos fuente de philisophers
SRCS =

# Convertimos los archivos .c en .o
OBJS = $(SRCS:.c=.o)

# Regla principal (compila el ejecutable)
all: $(NAME)

# Compilar push_swap
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Compilacion completada: $(NAME)"

# Regla para compilar archivos .c en .o de philisophers
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compilado: $<"

# Eliminar archivos .o
clean:
	@rm -f $(OBJS)
	@echo "Archivos objeto eliminados."

# Eliminar el ejecutable y los archivos objeto
fclean: clean
	@rm -f $(NAME)
	@echo "Ejecutable eliminado."

# Recompilar desde cero
re: fclean all