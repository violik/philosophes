##
## Makefile for make in /home/denel-_l/rendu/piscine_cpp_d01/ex01
##
## Made by denel lowik
## Login   <denel-_l@epitech.net>
##
## Started on  Wed Jan  7 11:36:20 2015 denel lowik
## Last update Wed Feb 25 10:48:11 2015 denel-_l
##

CC = gcc -lpthread

RM = rm -f

CFLAGS += -Wextra -Wall -Werror
CFLAGS += -ansi -pedantic
CFLAGS += -I.

NAME =	philo

SRCS =	Philo.c \
	Action.c

OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)
clean:
	$(RM) $(OBJS)

fclean: clean
	 $(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
