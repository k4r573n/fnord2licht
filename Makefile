run: serial2.o
	./fnord2licht 255 255 255 255

serial2.o: serial2.c
	gcc -o fnord2licht serial2.c

edit:
	vim serial2.c

clean:
	rm serial2.o

