NAME = RPN

CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98 -g

SRCS = main.cpp RPN.cpp
OBJS = $(SRCS:.cpp=.o)

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -fsanitize=address -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re