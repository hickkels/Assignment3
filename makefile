537ps:  537ps.o readproc.o parseopts.o output.o
	gcc -o 537ps 537ps.o readproc.o parseopts.o output.o
	echo built successfully....

537ps.o: 537ps.c 537ps.h readproc.h parseopts.h
	gcc -c -Wall -Wextra 537ps.c

readproc.o: readproc.c readproc.h
	gcc -c -Wall -Wextra readproc.c

parseopts.o: parseopts.c parseopts.h
	gcc -c -Wall -Wextra parseopts.c

output.o: output.c
	gcc -c -Wall -Wextra output.c
