NAME	=	minishell

OS		=	$(shell uname)

linuxDistr = $(shell cat /etc/*-release | grep "DISTRIB_ID" | cut -f2 -d"=")

HEADER	=	${SRCS}/{NAME}.h

LIBFT	=	./libft/libft.a

CFLAGS	=	-Wall -Werror -Wextra

SRCS	=	main.c	execute_simple_funcs.c	get_command_list_funcs.c \
			builtin_funcs1.c	builtin_funcs2.c

SRC_DIR	=	./srcs

D_SRCS	=	$(addprefix ${SRC_DIR}/,${SRCS})

OBJS	=	${D_SRCS:.c=.o}

CC		=	cc

%.o	:	%.c ${HEADER}
		${CC} ${CFLAGS} $< -c -o $@

ifeq (${OS},Linux)

 ifeq (${linuxDistr},Ubuntu)
${NAME}	:	${OBJS} ${LIBFT} bubunta
			${CC} ${CFLAGS} ${OBJS} -lreadline -L./libft -lft -o ${NAME}

 else ifeq (${linuxDistr},Arch)
${NAME}	:	${OBJS} ${LIBFT}
			${CC} ${CFLAGS} ${OBJS} -lreadline -L./libft -lft -o ${NAME}
 endif

else ifeq (${OS},Darwin)
${NAME}	:	${OBJS} ${LIBFT}
			${CC} ${CFLAGS} ${OBJS} -lreadline \
 			-L${HOME}/.brew/Cellar/readline/8.1.2/lib/ \
 			-I${HOME}/.brew/Cellar/readline/8.1.2/include/ \
 			-L./libft -lft -o ${NAME}

else

${NAME}	:
			echo "Unknown operating system, compilation won't start"
endif

.PHONY	:	all re clean fclean libft

all		:	${NAME}

${LIBFT} : libft ;

libft	:
			${MAKE} -C ./libft

bubunta	:
			sudo apt-get install libreadline-dev

clean	:
			rm -rf ${OBJS}
			${MAKE} -C ./libft clean

fclean	:	clean
			rm -rf ${NAME}
			${MAKE} -C ./libft fclean

re		: fclean all

ch_leaks :
			leaks -atExit -- ./${NAME}

sleeper	:	./info_resources/sleeper.o ${LIBFT}
			${CC} ${CFLAGS} $< -lft -L./libft -o sleeper
test	:
			echo ${linuxDistr}