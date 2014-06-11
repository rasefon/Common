Target = tt.out
Objects = main.o bitset.o st.o rw_io.o
Flags = -g -c -std=c99 -Wall
Include = common.h

$(Target): $(Objects)
	gcc -o $(Target) $(Objects)

main.o: main.c bitset.h $(Include)
	gcc $(Flags) main.c

bitset.o: bitset.c bitset.h $(Include)
	gcc $(Flags) bitset.c

st.o: st.c st.h 
	gcc $(Flags) st.c

rw_io.o: rw_io.c rw_io.h $(Include)
	gcc $(Flags) rw_io.c

clean:
	rm -rf *.o *.exe 
