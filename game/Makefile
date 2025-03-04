CFLAGS = -Wall -g -O

NAME = game

OBJ = view.o cmd_view.o gui_view.o model.o main.o controller.o


all: $(NAME)

%.o: %.cpp
	g++ -c -o $@ $^

$(NAME) : $(OBJ)
	g++ -o $(NAME) $^ $(CFLAGS)

clean:
	$(RM) $(OBJ) $(NAME)