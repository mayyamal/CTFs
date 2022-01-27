#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define _GNU_SOURCE
#include <unistd.h>
#include <sys/types.h>
int setresgid(gid_t rgid, gid_t egid, gid_t sgid);

void do_stuff()
{
	struct {
		char buffer_read[4];
		int i;
		char* current_token_char;
		char token[4];
		int canary; // To detect overflows
		char admin; // This should never be accessible
	} d;

	memset(&d, 0x00, sizeof(d));
	d.current_token_char = d.token;

	for (d.i = 0; d.i < 4; d.i++) {
		printf("Enter char %zu\n", d.i);
		if (fgets(d.buffer_read, 8, stdin) == 0) {
			printf("Failed to read char %d\n", d.i);
			return;
		}
		*d.current_token_char = d.buffer_read[0];
		d.current_token_char++;
	}

	if (strncmp(d.token,"ABCD", 4) == 0) {
		printf("token correct\n");
		printf("Here's your new secure PIN: 4284\n");
	} else {
		printf("You entered %c%c%c%c, which is not correct.\n",
			d.token[0], d.token[1], d.token[2], d.token[3]);
		exit(1);
	}

	if (d.canary != 0xDEADBEEF) {
		printf("Canary tweets 'my stack is corrupted!'\n");
		exit(1);
	}

	if (d.admin) {
		system("cat flag.txt");
	}
}

int main(int argc, char** argv) {
	gid_t gid = getegid();
  	setresgid(gid,gid,gid);
	do_stuff();
	printf("bye\n");
	exit(0);
}
