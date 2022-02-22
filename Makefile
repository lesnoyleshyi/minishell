NAME		=	minishell

INCLUDES	=	./includes

SRC_DIR		=	./srcs

HEADER		=	${INCLUDES}/${NAME}.h

LIBFT		=	./libft/libft.a

CFLAGS		=	-Wall -Werror -Wextra

SRCS	=	main.c	\
			data/common.c	data/data.c		data/list.c		data/param.c	data/file.c		data/string_array.c\
			utils/first_parser.c	utils/replace_param.c	utils/get_mod_file.c	utils/second_parser.c	utils/read_heredoc.c	utils/choice_builtin.c\
			string/get_substr.c		string/insert_str.c		string/get_unsubstr.c	string/ft_strcmp.c string/remove_all_quote.c	string/remove_string.c\
			checks/check_function.c	checks/check_get_param.c	checks/check_determinate.c	checks/check_content.c \
			xlam/print.c \
			$(addprefix builtins/,env.c export.c) \
			$(addprefix execute/,execute_funcs.c choose_input.c choose_output.c get_abs_path.c) \
			$(addprefix signal/,signal_funcs.c)

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