run: serial2.o
	./serial-ansteuer-prog 255 255 255 255

serial2.o: serial2.c
	gcc -o serial-ansteuer-prog serial2.c 

edit:
	vim serial2.c

clean:
	rm serial2.o

