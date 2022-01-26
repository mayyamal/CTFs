all: test.c test2.c
	gcc -fno-stack-protector -m32 -O0 -g test.c -o test
	execstack -s test

test2:
	gcc -fno-stack-protector -m32 -O0 -g test2.c -o test2
	execstack -s test2
clean:
	rm test
	