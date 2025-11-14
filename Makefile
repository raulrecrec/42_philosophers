# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/25 16:25:10 by rexposit          #+#    #+#              #
#    Updated: 2025/11/14 22:03:27 by rexposit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del ejecutable
NAME = philo

# Compilador y flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I.
#CFLAGS += -g3 -fsanitize=thread
# Archivo fuente de philisophers
SRCS =	philosophers.c

# Archivos fuente utils
SRCS +=	utils/ph_atoll.c	\
		utils/ph_error.c	\
		utils/ph_isdigit.c	\
		utils/ph_malloc.c	\
		utils/ph_strlen.c	\
		utils/ph_time.c

# Archivos fuente core
SRCS +=	core/setup_alloc.c		\
		core/init_mutexes.c		\
		core/init_philos.c		\
		core/state.c			\
		core/philo_routine.c	\
		core/monitor.c			\
		core/cleanup.c			\
		core/threads.c

# Convertimos los archivos .c en .o
OBJS = $(SRCS:.c=.o)

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

# Headers
HEADERS = philosophers.h
$(OBJS): $(HEADERS)

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

print-%:
	@echo '$* = $($*)'


.PHONY: all clean fclean re