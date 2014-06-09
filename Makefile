Target = tt
Objects = main.o bitmap.o st.o rw_io.o
Flags = -g -c -std=c99
Include = common.h

$(Target): $(Objects)
	gcc -o $(Target) $(Objects)

main.o: main.c bitmap.h $(Include)
	gcc $(Flags) main.c

bitmap.o: bitmap.c bitmap.h $(Include)
	gcc $(Flags) bitmap.c

st.o: st.c st.h 
	gcc $(Flags) st.c

rw_io.o: rw_io.c rw_io.h $(Include)
	gcc $(Flags) rw_io.c

clean:
	rm -rf *.o *.exe 
