NAME	=	minishell

LIBFT	=	./libft/libft.a

CFLAGS	=	-Wall -Werror -Wextra

SRCS	=	main.c	\
			data/common.c			data/data.c				data/list.c			data/param.c	data/file.c	data/string_array.c\
			utils/first_parser.c	utils/replace_param.c	utils/get_mod_file.c	utils/second_parser.c\
			string/get_substr.c			string/insert_str.c	string/get_unsubstr.c	string/ft_strcmp.c string/remove_all_quote.c\
			checks/check_function.c	checks/check_get_param.c	checks/check_determinate.c	checks/check_content.c \
			xlam/print.c
OBJS	=	${SRCS:.c=.o}

CC		=	gcc

%.o	:	%.c
		${CC} $< -c -o $@

${NAME}	:	${LIBFT} ${OBJS}
			${CC} ${OBJS} -lreadline \
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