shell : shell.o shell_lib.o
	gcc shell.o shell_lib.o -o shell
shell.o: shell.cpp
	gcc  -c shell.cpp  -o shell.o
shell_lib.o: shell_lib.cpp	
	gcc -c shell_lib.cpp -o shell_lib.o
clear:
	rm -f shell.o shell_lib.o shell