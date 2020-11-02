CC = gcc
WARNING_FLAGS = -g -Wall -Wextra
#
# Sample makefile updated to include the commands to run the Clang Static Analyzer
#
#    scan-build will "make" your program and run CSA at the same time.
#
#    scan-view will do a scan-build (if necessary) and then open a web browser
#      window to review the results.
#
CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = 537make
SCAN_BUILD_DIR = scan-build-out

all: main.o textparser.o buildgraph.o buildrep.o proccreate.o
	$(CC) -o $(EXE) main.o textparser.o buildgraph.o buildrep.o proccreate.o

main.o: main.c buildrep.h buildgraph.h proccreate.h textparser.h 
	$(CC) -c $(WARNING_FLAGS) main.c

textparser.o: textparser.c textparser.h buildrep.h
	$(CC) -c $(WARNING_FLAGS) textparser.c

buildgraph.o: buildgraph.c buildgraph.h buildrep.h
	$(CC) -c $(WARNING_FLAGS) buildgraph.c

buildrep.o: buildrep.c buildrep.h
	$(CC) -c $(WARNING_FLAGS) buildrep.c

proccreate.o: proccreate.c proccreate.h
	$(CC) -c $(WARNING_FLAGS) proccreate.c

clean:
	rm -f $(EXE) *.o
	rm -rf $(SCAN_BUILD_DIR)

#
# Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
# View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html
