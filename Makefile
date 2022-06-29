clean:
	rm -rf `find . -type d -name 'testFiles*'`

init: setupexec
	./setupexec

setupexec: setup.c
	gcc -o setupexec setup.c