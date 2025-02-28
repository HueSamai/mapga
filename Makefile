all: build test

build:
	clang mapga.c -c -o mapga.o
test:
	clang mapga.o test.c -o test
	chmod +x test
	./test
