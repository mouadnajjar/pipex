# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 19:43:59 by monajjar          #+#    #+#              #
#    Updated: 2025/03/16 16:08:22 by monajjar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= pipex

SRCS := utils.c utils2.c pipex.c execution.c utils3.c \

OBJS := $(SRCS:.c=.o)

HEADER := pipex.h

CFLAGS := -Wall -Wextra -Werror

CC := cc

all: $(NAME)

$(NAME): $(OBJS)
		@make -C libft
		@cp -rf libft/libft.a .
		$(CC) $(CFLAGS) $(OBJS) libft.a -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C libft
	rm -rf $(OBJS)
fclean : clean
	rm -rf $(NAME) libft.a libft/libft.a
re: fclean all

.SECONDARY: $(OBJS)

.PHONY: all clean fclean re