#include <unistd.h>
#include <stdio.h>

int main() {
	

	int x;
	printf("address of x = %p\n", &x);
	printf("address of main = %p\n", &main);
	//system("ls -l");
	//printf("address of system = %p\n", &system);

	sleep(5);
	return 0;
}