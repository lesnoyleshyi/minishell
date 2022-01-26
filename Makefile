NAME	=	minishell

CFLAGS	=	-Wall -Werror -Wextra

SRCS	=	main.c

OBJS	=	${SRCS:.c=.o}

CC		=	cc

%.o	:	%.c
		${CC} ${CFLAGS} $< -c -o $@

${NAME}	:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -lreadline \
 			-L${HOME}/.brew/Cellar/readline/8.1.2/lib/ \
 			-I${HOME}/.brew/Cellar/readline/8.1.2/include/  -o ${NAME}

all		:	${NAME}

clean	:
			rm -rf ${OBJS}

fclean	:	clean
			rm -rf ${NAME}

re		: fclean all