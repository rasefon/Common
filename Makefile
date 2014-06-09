Target = tt
Objects = main.o bitmap.o
Flags = -g -c -std=c99

$(Target): $(Objects)
	gcc -o $(Target) $(Objects)

main.o: main.c bitmap.h
	gcc $(Flags) main.c

bitmap.o: bitmap.c bitmap.h
	gcc $(Flags) bitmap.c

clean:
	rm -rf *.o *.exe 
