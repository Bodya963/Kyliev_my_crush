CFLAGS = -Wall -g -O

NAME = word_counter

OBJ = floy.o parser.o library.o main.o

all: $(NAME)

%.o: %.cpp
	gcc -c -o $@ $^

$(NAME) : $(OBJ)
	gcc -o $(NAME) $^ $(CFLAGS)

clean:
	$(RM) $(OBJ) $(NAME)