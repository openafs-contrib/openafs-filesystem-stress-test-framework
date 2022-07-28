clean:
	rm -rf `find . -type d -name 'testFiles*'`
	rm -f cpu-time.txt
	rm -f files-used.txt

removeexec:
	rm -f setupexec
	rm -f setup
	rm -f fileexec-1
	rm -f fileexec-2
	rm -f filemonkeytester
	rm -f fileexec

init: setupexec
	./setupexec

setupexec: setup.c config-parser.c
	gcc -o setupexec setup.c config-parser.c -Wall

run: fileexec
	./fileexec

fileexec: filetest filetester.c config-parser.c
	gcc -o fileexec filetester.c config-parser.c -Wall

filetest: filemonkeytest.c fileoperations.c config-parser.c
	gcc -o filemonkeytester filemonkeytest.c fileoperations.c config-parser.c -Wall

fileexec-1: fileoperations.c filemonkeytest-1.c
	gcc -o fileexec-1 filemonkeytest-1.c fileoperations.c -Wall

fileexec-2: fileoperations.c filemonkeytest-2.c
	gcc -o fileexec-2 filemonkeytest-2.c fileoperations.c -Wall
reset: clean init run