SRCS = main.cpp map.cpp stack.cpp utils.cpp vector.cpp

OBJS = ${SRCS:.cpp=.o}

FLAGS = -Wall -Wextra -Werror

CC = c++ -std=c++98

NAME = containers

all: ${NAME}

${NAME}: std ft

$(OBJS):
	$(CC) -c $(FLAGS) $(SRCS)

ft: clean
	$(CC) -c $(FLAGS) -D ns=ft $(SRCS)
	$(CC) $(FLAGS) $(OBJS) -o ft_containers

std: clean
	$(CC) -c $(FLAGS) -D ns=std $(SRCS)
	$(CC) $(FLAGS) $(OBJS) -o std_containers

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f ft_containers
	rm -f std_containers

re: fclean all

.PHONY:	all clean fclean re ft std bonus