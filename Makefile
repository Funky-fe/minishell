NAME		= minishell
LIBFT_DIR	= libft/
LIBFT		= ${LIBFT_DIR}libft.a
SRC			= minishell.c utils.c free.c \
			  lexer.c \
			  parser.c
OBJ_DIR		= objects/
OBJ			= ${addprefix ${OBJ_DIR}, ${SRC:%.c=%.o}}
VPATH		= sources sources/builtin
INCLUDES	= headers/ ${LIBFT_DIR}
INCLUDES	:= ${addprefix -I, ${INCLUDES}}
CC			= cc
CFLAGS		=
RLFLAGS		= -lreadline
RM			= rm -rf

all: ${NAME}

$(NAME): ${LIBFT} ${OBJ_DIR} ${OBJ}
	${CC} ${CFLAGS} ${OBJ} ${INCLUDES} ${LIBFT} ${RLFLAGS} -o ${NAME}

clean:
	make clean -C ${LIBFT_DIR}
	${RM} ${OBJ_DIR}

fclean: clean
	make fclean -C ${LIBFT_DIR}
	${RM} ${NAME}

re: fclean all

${LIBFT}:
	make -C ${LIBFT_DIR}

${OBJ_DIR}:
	mkdir -p ${OBJ_DIR}

${OBJ_DIR}%.o: %.c
	${CC} -c ${CFLAGS} ${INCLUDES} $< -o $@

.PHONY: all clean fclean re
