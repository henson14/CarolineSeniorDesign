all:
	gcc -I build/include -L build/lib -o main code/main.c - lmingw32 - lSDL2main - lSDL2