# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/25 16:25:10 by rexposit          #+#    #+#              #
#    Updated: 2025/10/14 20:41:48 by rexposit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del ejecutable
NAME = philo

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -pthread

# Archivo fuente de philisophers
SRCS =	philosophers.c	\

# Archivos fuente utils
SRCS +=	utils/ph_atoll.c	\
		utils/ph_error.c	\
		utils/ph_isdigit.c	\
		utils/ph_malloc.c	\
		utils/ph_strlen.c	\
		utils/ph_time.c	

# Archivos fuente core
SRCS +=	core/setup_alloc.c	\
		core/init_mutexes.c

# Convertimos los archivos .c en .o
OBJS = $(SRCS:.c=.o)

# Headers
HEADERS = philosophers.h
$(OBJS): $(HEADERS)

# Regla principal (compila el ejecutable)
all: $(NAME)

# Compilar philosophers
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

.PHONY: all clean fclean re