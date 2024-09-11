all:
	gcc -I build/include -L build/lib -o main code/main.c code/imageConversion.c -lSDL2main -lSDL2