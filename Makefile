NAME	=	minishell

HEADER	=	${SRCS}/{NAME}.h

LIBFT	=	./libft/libft.a

CFLAGS	=	-Wall -Werror -Wextra

SRCS	=	main.c	execute_funcs.c	get_command_list_funcs.c \
			builtin_funcs1.c	builtin_funcs2.c	open_files_funcs.c

SRC_DIR	=	./srcs

D_SRCS	=	$(addprefix ${SRC_DIR}/,${SRCS})

OBJS	=	${D_SRCS:.c=.o}

CC		=	cc

%.o	:	%.c ${HEADER}
		${CC} ${CFLAGS} $< -c -o $@

${NAME}	:	${OBJS} ${LIBFT}
			${CC} ${CFLAGS} ${OBJS} -lreadline \
 			-L${HOME}/.brew/Cellar/readline/8.1.2/lib/ \
 			-I${HOME}/.brew/Cellar/readline/8.1.2/include/ \
 			-L./libft -lft -o ${NAME}

.PHONY	:	all re clean fclean libft

all		:	${NAME}

${LIBFT} : libft ;

libft	:
			${MAKE} -C ./libft

clean	:
			rm -rf ${OBJS}
			${MAKE} -C ./libft clean

fclean	:	clean
			rm -rf ${NAME}
			${MAKE} -C ./libft fclean

re		: fclean all

ch_leaks :
			leaks -atExit -- ./${NAME}