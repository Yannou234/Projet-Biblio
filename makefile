all: biblio

book.o: compilationV2.h book.c
	gcc -c book.c -o book.o

main.o: compilationV2.h mainV2.c
	gcc -c mainV2.c -o main.o

biblio: book.o main.o
	gcc book.o main.o -o biblio
