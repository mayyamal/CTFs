#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//Exploit a format string vulnerability in order to make the program reveal the hidden
//NSA information ;)
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>

int setresgid(gid_t rgid, gid_t egid, gid_t sgid);
#define DEBUG_LEVEL 0
#define WARNING(level, msg) if (level >= DEBUG_LEVEL) fprintf(stdout, "Warning: %s\n", msg)
#define ERROR(msg) fprintf(stderr, "Error: %s\n", msg)
#define LOG(...) fprintf(stdout, __VA_ARGS__)
#define PRINT_HEX(buf, len) do { for (size_t i = 0; i < len; i++) printf("%02x", (unsigned char)buf[i]); } while(0)

char tmp[256];
void logging(char* cmd) {
	if (strlen(cmd) >= sizeof(tmp)) {
		ERROR("Stop talkin' dude!\n");
		exit(1);
	}
	snprintf(tmp, sizeof(tmp), "[%lu]: %s\n", time(NULL), cmd);
	LOG(tmp);
}

int command(char* cmd){
	printf("Yo dawg, what r ya doin right now?\n");
	logging(cmd);
	if (!strcmp(cmd, "gimme-rnd")) {
		system("fortune -s");
	} else if (!strcmp(cmd, "gimme-null")) {
		system("cat /dev/null");
	} else if (!strcmp(cmd, "gimme-flag")) {
		puts("Nice try. Forget it!\n");
	} else if (!strcmp(cmd, "gimme-cipher")) {
		return 1;
	} else {
		puts("Didn't get it :{\n");
	}
	return 0;
}

void encrypt(char* msg, size_t len) {
	int fd = open("/dev/urandom", O_RDONLY);
	assert(fd >= 0);
	char otp[len];
  assert(read(fd, otp, len) == len);
  for (size_t i = 0; i < len; i++) {
		msg[i] ^= otp[i];
	}
}

int main(int argc, char** argv){
	gid_t gid = getegid();
  	setresgid(gid,gid,gid);
	char* nsa_document = "\n\
	Dear Mr President,\n\
	we found out a very import information";
	FILE* f = fopen("flag.txt", "r");
	assert(f);
	char secret[128];
	assert(fread(secret, 1, sizeof(secret), f) > 0);
	
	if(argc == 2) {
		if (command(argv[1])) {
			encrypt(secret, sizeof(secret));
			PRINT_HEX(secret, sizeof(secret));
		}
	} else {
		WARNING(1, "I am single-threaded!\n");
	}
	
	// safe cleanup
	memset(secret, 0, sizeof(secret));
}
