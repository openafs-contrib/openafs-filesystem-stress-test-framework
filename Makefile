clean:
	@echo "Cleaning test files..."
	@rm -rf `find . -type d -name 'testFiles*'`
	@rm -rf metrics
	@rm -f log.txt
	@rm -f pylog.txt
	@echo "Cleaned"
	@rm -rf test-directory

removeexec:
	rm -f setupexec
	rm -f setup
	rm -f fileexec-1
	rm -f fileexec-2
	rm -f filemonkeytester
	rm -f fileexec

init: setupexec
	@echo "Setting up test directories and files... (Will take some time)"
	@./setupexec > log.txt

setupexec: setup.c config-parser.c
	@gcc -o setupexec setup.c config-parser.c -Wall

run: fileexec
	@echo "Running test suite..."
	@./fileexec > log.txt

fileexec: filetest filetester.c config-parser.c
	@gcc -o fileexec filetester.c config-parser.c -Wall

filetest: filemonkeytest.c fileoperations.c config-parser.c
	@gcc -o filemonkeytester filemonkeytest.c fileoperations.c config-parser.c -Wall

reset: clean init run

viewplots: requirements.txt metrics-scraper.py
	@pip install -r requirements.txt > pylog.txt
	@python3 metrics-scraper.py
