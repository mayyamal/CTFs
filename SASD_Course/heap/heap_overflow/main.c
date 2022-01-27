#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/types.h>
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>

char flag[128];

int setresgid(gid_t rgid, gid_t egid, gid_t sgid);

struct created_chunk
{
	int size;
	char* name;
};

struct created_chunk created_chunklist[100] = {0}; 

void prologue()
{
	puts("Hello;)");
}

void epilogue() 
{
	puts("See yah;)");
}

struct chunk
{
	void (*prologue)();
	void (*epilogue)();
};

void printHelp()
{
	puts("----------------------------");
	puts("1.show the created_chunks in the heap struct");
	puts("2.add a new created_chunk");
	puts("3.change the created_chunk in the heap struct");
	puts("4.remove the created_chunk in the heap struct");
	puts("5.exit");
	puts("----------------------------");
	puts("Your menu created_chunk:");
}

int choice;

void showChunk()
{
	int counter;
	if(!choice)
	{
		puts("No created_chunk in the chunk");		
	}
	else
	{
		for(counter = 0;counter < 100;counter++)
		{
			if(created_chunklist[counter].name)
			{
				printf("%d : %s",counter,created_chunklist[counter].name);
			}
		}
		puts("");
	}
}

int addChunk()
{
	char sizebuf[8];
	int length;
	int i;
	int size;
	if(choice < 100)
	{
		printf("Please enter the length of created_chunk name:");
		read(0,sizebuf,8);
		length = atoi(sizebuf);
		if(length == 0)
		{
			puts("invalid length");
			return 0;
		}
		for(i = 0; i < 100; i++)
		{
			if(!created_chunklist[i].name)
			{
				created_chunklist[i].size = length;
				created_chunklist[i].name = (char*)malloc(length);
				printf("Please enter the name of created_chunk:");
				size = read(0,created_chunklist[i].name,length);
				created_chunklist[i].name[size] = '\x00';
				choice++;
				break;
			}
		}
	
	}
	else
	{
		puts("the chunk is full");
	}
	return 0;
}



void modifyChunk()
{
	char indexbuf[8];
	char lengthbuf[8];
	int length;
	int index;
	int readsize;

	if(!choice)
	{
		puts("No created_chunk in the chunk");
	}
	else
	{
		printf("Please enter the index of the created_chunk:");
		read(0,indexbuf,8);
		index = atoi(indexbuf);
		if(created_chunklist[index].name)
		{
			printf("Please enter the length of the created_chunk's name:");
			read(0,lengthbuf,8);
			length = atoi(lengthbuf);
			printf("Please enter the new name of the created_chunk:");
			readsize = read(0,created_chunklist[index].name,length);
			*(created_chunklist[index].name + readsize) = '\x00';
		}else
		{
			puts("invalid index");
		}
		
	}	

}

void deleteChunk(){
	char indexbuf[8];
	int index;

	if(!choice)
	{
		puts("No created_chunk in the chunk");
	}
	else
	{
		printf("Please enter the index of created_chunk:");
		read(0,indexbuf,8);
		index = atoi(indexbuf);
		if(created_chunklist[index].name){
			free(created_chunklist[index].name);
			created_chunklist[index].name = 0;
			created_chunklist[index].size = 0;
			puts("remove successful!!");
			choice--;			
		}else{
			puts("invalid index");
		}
	}
}

void printFlag()
{
  printf("Enjoy your flag: %s\n",flag);
}

int main()
{	
	FILE* f = fopen("flag.txt", "r");
	assert(f);	
	assert(fread(flag, 1, sizeof(flag), f) > 0);
	fclose(f);
	gid_t gid = getegid();
  	setresgid(gid,gid,gid);
	char buffer[8];
	int choice;
	struct chunk* created_chunk;
	setvbuf(stdout,0,2,0);
	setvbuf(stdin,0,2,0);
	created_chunk = malloc(sizeof(struct chunk));
	created_chunk->prologue = prologue;
	created_chunk->epilogue = epilogue;
	created_chunk->prologue();
	while(1)
	{
		printHelp();
		read(0,buffer,8);
		choice = atoi(buffer);
		switch(choice){
			case 1:
				showChunk();
				break;
			case 2:
				addChunk();
				break;
			case 3:
				modifyChunk();
				break;
			case 4:
				deleteChunk();
				break;
			case 5:
				created_chunk->epilogue();
				exit(0);
				break;
			default:
				puts("invalid choice!!!");
				break;
		
		}	
	}

	return 0;
}
