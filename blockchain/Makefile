#-*- MakeFile -*-

all: blockchain
	
blockchain:
	gcc -g -fsanitize=address *.c headers.h -o blockchain
run:
	clear && ./blockchain ; rm blockchain
w:
	gcc -g -fsanitize=address -Wall -Wextra -Werror *.c headers.h -o blockchain
d:
	lldb *.c headers.h -o blockchain


clean:
	rm *.o *.h.gch core.* a.out blockchain
