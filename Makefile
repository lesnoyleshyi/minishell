NAME		=	minishell

INCLUDES	=	./includes

SRC_DIR		=	./srcs

HEADER		=	${INCLUDES}/${NAME}.h

LIBFT		=	./libft/libft.a

CFLAGS		=	-Wall -Werror -Wextra

SRCS	=	main.c	\
			xlam/print.c \
			$(addprefix data/, common.c	data.c list.c param.c file.c string_array.c) \
			$(addprefix utils/, first_parser.c replace_param.c get_mod_file.c \
						second_parser.c read_heredoc.c execute_builtin.c history.c) \
			$(addprefix string/, get_substr.c insert_str.c get_unsubstr.c \
						ft_strcmp.c remove_all_quote.c remove_string.c) \
			$(addprefix checks/, check_function.c check_get_param.c check_determinate.c \
						check_content.c check_param_name.c check_presence_param.c check_common.c)\
			$(addprefix builtins/, cd.c echo.c env.c exit.c export.c unset.c pwd.c) \
			$(addprefix execute/, execute_funcs.c choose_input.c choose_output.c get_abs_path.c execute_simple.c new_env.c) \
			$(addprefix signal/, signal_funcs.c) \
			$(addprefix error/, error.c)

D_SRCS	=	$(addprefix ${SRC_DIR}/,${SRCS})

OBJS	=	${D_SRCS:.c=.o}

CC		=	cc

OS		=	$(shell uname)

%.o	:		%.c	${HEADER}
			${CC} ${CFLAGS} -c $< -o $@

ifeq (${OS},Linux)

linuxDistr	=	$(shell cat  /etc/*-release | grep "DISTRIB_ID" | cut -f2 -d="=")

ifeq (${linuxDistr},Ubuntu)
${NAME}	:	${OBJS} ${LIBFT} bubunta
			echo "hello, bubunta user"
			${CC} ${CFLAGS} ${OBJS} -lreadline -L./libft -lft -o ${NAME}
else ifeq (${linuxDistr},Arch)
${NAME}	:	${OBJS} ${LIBFT}
			echo "Hello, arch user"
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

clean	:
			rm -rf ${OBJS}
			${MAKE} -C ./libft clean

fclean	:	clean
			rm -rf ${NAME}
			${MAKE} -C ./libft fclean

re		: fclean all

ch_leaks :
			leaks -atExit -- ./${NAME}