#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <sys/types.h>
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>

int setresgid(gid_t rgid, gid_t egid, gid_t sgid);

char secret_key[16];

void init(){
	char secret[16];
	for (size_t i = 0; i < 16; i++) {
		secret[i] = 'a' + rand() % 26;
	}
	memcpy(secret_key, secret, 16);
}

void process_user_input()
{
	printf("Please enter the secret password\n");
	char user_input[16];
	for (size_t i = 0; i < 15; i++) {
		int c = getchar();
		if(c == EOF)
			break;
		user_input[i] = c;
		user_input[i + 1] = '\0';
	}
	printf("You entered \"%s\"\n", user_input);
	if(strncmp(user_input, secret_key, 16) == 0) {
		printf("Congratulations that was the correct password!\n");
		system("cat flag.txt");
	} else {
		printf("Wrong password\n");
	}
}

int main(int argc, char** argv){
	gid_t gid = getegid();
  	setresgid(gid,gid,gid);
	srand(time(0));
	init();
	process_user_input();
}
