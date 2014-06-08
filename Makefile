Target = tt
Objects = bitmap.o
Flags = -g -c -std=c99

$(Target): $(Objects)
	gcc -o $(Target) $(Objects)

bitmap.o: bitmap.h
	gcc $(Flags) bitmap.c

clean:
	rm -rf *.o *.exe 
