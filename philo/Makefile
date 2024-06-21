# bin
NAME = philo

# Directories
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc

# Sources files
SRCS = main.c \
	utils.c

OBJS = ${addprefix ${OBJ_DIR}/, ${SRCS:.c=.o}}

# Compilations
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CLINKS = -lpthread -I ${INC_DIR}


${OBJ_DIR}/%.o : ${SRC_DIR}/%.c
	@mkdir -p ${@D}
	${CC} ${CFLAGS} -c $< -o $@ ${CLINKS}

${NAME} : ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${CLINKS}

all	: ${NAME}

clean :
	rm -f ${OBJS}
	@rmdir ${OBJ_DIR} 2> /dev/null || true

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY : all clean fclean re