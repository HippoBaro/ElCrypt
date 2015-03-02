##
## Makefile for ELCrypt in /home/barrau_h/Desktop/rush
## 
## Made by Hippolyte Barraud
## Login   <barrau_h@epitech.net>
## 
## Started on  Fri Feb 27 22:22:00 2015 Hippolyte Barraud
## Last update Sun Mar  1 21:47:38 2015 Hippolyte Barraud
##

CC              =       gcc -g

NAME		=	elcrypt

SRCS		=	./srcs/main.c			\
			./srcs/miscs.c			\
			./srcs/query_parser/parser.c	\
			./srcs/key/key.c		\
			./srcs/key/key_gen.c		\
			./srcs/cipher/cipher.c		\
			./srcs/cipher/padding.c

OBJS		=	$(SRCS:.c=.o)

CFLAGS          =       -Wall -W -Werror -pedantic -ansi

RM              =       rm -f

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CC) -o $(NAME) $(OBJS)

clean		:
			$(RM) $(OBJS) 

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean re
