all:
	g++ sh_read.c -lpthread -o read.out
	g++ sh_write.c -lpthread -o write.out
	echo "!Please start read.out in another console"
	./write.out

compile:
	g++ sh_read.c  -o read.out
	g++ sh_write.c -o write.out
debug:
	echo "Write debug make"