# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/29 17:18:43 by tefroiss          #+#    #+#              #
#    Updated: 2021/07/13 15:02:34 by tefroiss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	philo_bonus

OS			=	$(shell uname)

SRCS		=	srcs/basic/ft_args.c		\
				srcs/basic/ft_atoi.c		\
				srcs/basic/ft_cinset.c		\
				srcs/basic/ft_isdigit.c		\
				srcs/basic/ft_isnumber.c	\
				srcs/basic/ft_isspace.c		\
				srcs/ft_get_get.c			\
				srcs/control_n_launch.c		\
				srcs/philo_time.c			\
				srcs/philo_act.c			\
				srcs/philo_act_fork.c
				
ifeq ($(OS), Linux)
	SRCS	+=	srcs/free_all_linux.c
else
	SRCS	+=	srcs/free_all_mac.c
endif

MAIN 		= 	srcs/main.c

OBJS_MAIN 	= 	$(MAIN:.c=.o)
OBJS		=	$(SRCS:.c=.o)

CC			=	clang

CFLAGS		+=	-Wall -Wextra -Werror

RM			=	rm -f

CLEAN		=	clean

INCLUDES	=	./includes/philo_bonus

#############################################################################
#									MAKE									#
#############################################################################

%.o			:	%.c ${INCLUDES}
				$(CC) $(CFLAGS) -c $< -o $@

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(OBJS_MAIN)
				${CC} ${CFLAGS} ${OBJS} ${OBJS_MAIN} -o ${NAME} -lpthread

clean		:
				$(RM) $(OBJS)
				$(RM) ${OBJS_MAIN}

fclean		:	clean
				$(RM) $(NAME)

re			:	fclean all

full		:	re
				$(RM) $(OBJS)
				$(RM) ${OBJS_MAIN}

.PHONY		:	all clean fclean re full