SRCS	= tester/test.cpp tester/vector_test.cpp tester/Foo.cpp tester/stack_test.cpp tester/test_utils.cpp tester/set_test.cpp \
		tester/map_test.cpp

OBJS	= ${SRCS:.cpp=.o}

OBJBS	= ${SRCS:.cpp=.o}

NAMESPACE = -D NAMESPACE=ft

NAME	= test

CXX	= c++

RM	= rm -f

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 #-fsanitize=address -g3

.cpp.o:
		${CXX} ${CXXFLAGS} ${NAMESPACE} -c $< -o ${<:.cpp=.o}

${NAME}:	${OBJS}
				${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

all:		${NAME}

clean:
				${RM} ${OBJBS} ${OBJS}

fclean: 	clean
				${RM} ${NAME}
				${RM} ${STDNAME}

re: 		fclean all

.PHONY:		all clean fclean re