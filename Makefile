clean:
	rm -rf `find . -type d -name 'testFiles*'`
	rm cpu-time.txt
	rm files-used.txt

init: setupexec
	./setupexec

setupexec: setup.c
	gcc -o setupexec setup.c -Wall

run: fileexec
	./fileexec

fileexec: fileexec-1 fileexec-2 filetester.c
	gcc -o fileexec filetester.c

fileexec-1: fileoperations.c filemonkeytest-1.c
	gcc -o fileexec-1 filemonkeytest-1.c fileoperations.c -Wall

fileexec-2: fileoperations.c filemonkeytest-2.c
	gcc -o fileexec-2 filemonkeytest-2.c fileoperations.c -Wall
reset: clean init run