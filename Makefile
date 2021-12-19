puissance4: board.o helpers.o play.o main.o
	gcc -Wall -Wextra board.o helpers.o play.o main.o -o puissance4 -fsanitize=leak -fsanitize=address 

helpers.o: helpers/helpers.h helpers/helpers.c
	gcc -Wall -Wextra -c helpers/helpers.c -o helpers.o -fsanitize=leak -fsanitize=address 

board.o: board/board.h board/board.c
	gcc -Wall -Wextra -c board/board.c -o board.o -fsanitize=leak -fsanitize=address 

play.o: play/play.h play/play.c 
	gcc -Wall -Wextra -c play/play.c -o play.o -fsanitize=leak -fsanitize=address 

main.o: main.c
	gcc -Wall -Wextra -c main.c -o main.o -fsanitize=leak -fsanitize=address 

run:
	./puissance4

tests: puissance4
	$(MAKE) -C testbed

cls:
	clear

clean:
	rm -rf *.o puissance4
	$(MAKE) -C testbed clean
	$(MAKE) cls

rebuild: 
	$(MAKE) clean 
	$(MAKE) puissance4