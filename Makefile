SRCS = main.cpp map.cpp stack.cpp utils.cpp vector.cpp

SRCB = main_bonus.cpp set.cpp

RBSRC = RBtest.cpp RBTree.cpp

OBJS = ${SRCS:.cpp=.o}

OBJB = ${SRCB:.cpp=.o}

RBOBJ = ${RBSRC:.cpp=.o}

FLAGS = -Wall -Wextra -Werror -g

CC = clang++ -std=c++98

NAME = containers

all: ${NAME}

$(OBJS):
	$(CC) -c $(FLAGS) -D ns=std $(SRCS)

$(OBJB):
	$(CC) -c $(FLAGS) -D ns=std $(SRCB)

${NAME}: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(addprefix std_, $(NAME))
	$(CC) -c $(FLAGS) -D ns=ft $(SRCS)
	$(CC) $(FLAGS) $(OBJS) -o $(addprefix ft_, $(NAME))

ft: clean
	$(CC) -c $(FLAGS) -D ns=ft $(SRCS)
	$(CC) $(FLAGS) $(OBJS) -o ft_containers

std: clean
	$(CC) -c $(FLAGS) -D ns=std $(SRCS)
	$(CC) $(FLAGS) $(OBJS) -o std_containers

bonus: $(OBJB)
	$(CC) $(FLAGS) $(OBJB) -o std_set
	$(CC) -c $(FLAGS) -D ns=ft $(SRCB)
	$(CC) $(FLAGS) $(OBJB) -o ft_set

RBtest: $(RBOBJ)
	$(CC) -c $(FLAGS) $(RBSRC)
	$(CC) $(FLAGS) $(RBOBJ) -o RBtest

clean:
	rm -f $(OBJS)
	rm -f $(OBJB)
	rm -f $(RBOBJ)

fclean: clean
	rm -f ft_containers
	rm -f std_containers
	rm -f ft_set
	rm -f std_set
	rm -f RBtest

re: fclean all

.PHONY:	all clean fclean re ft std bonus
