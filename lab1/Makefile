all:run
build:
	g++ main.c -o main
run: build
	[ -f "res.txt"] && rm res.txt || echo 
	./main > res.txt
	cat res.txt
