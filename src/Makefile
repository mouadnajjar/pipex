# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 13:30:57 by monajjar          #+#    #+#              #
#    Updated: 2025/02/28 12:57:09 by monajjar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= pipex

SRCS := utils.c pipex.c execution.c \

OBJS := $(SRCS:.c=.o)

FLAGS := -Wall -Wextra -Werror -g

CC := cc

all: $(NAME)

$(NAME): $(OBJS)
		make -C ../libft
		cp -rf ../libft/libft.a ../src
		$(CC) $(FLAGS) $(OBJS) libft.a -o $(NAME)
clean:
	make clean -C ../libft
	rm -rf $(OBJS)
fclean : clean
	rm -rf $(NAME) libft.a ../libft/libft.a
re: fclean all

.SECONDARY: $(OBJS)