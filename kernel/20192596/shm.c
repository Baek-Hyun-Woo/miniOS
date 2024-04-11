#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>

int producer()
{
	const int SIZE = 4096; // size of shared memory
	const char *name = "OS"; // name of shared memory object
	const char *message_0 = "Hello";
	const char *message_1 = "World!";
	int fd; // shared memory file descriptor
	char *ptr; // pointer to shared memory object
	fd = shm_open(name, O_CREAT | O_RDWR, 0666); // create shared memory object
	ftruncate(fd,SIZE); // configure the size of shared memory
	ptr = (char*)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	sprintf(ptr, "%s", message_0);
	ptr += strlen(message_0);
	sprintf(ptr, "%s", message_1);
	ptr += strlen(message_1);
	return 0;
}

int consumer()
{
	const int SIZE = 4096; // size of shared memory
	const char *name = "OS"; // name of shared memory object
	int fd;
	char *ptr;
	fd = shm_open(name, O_RDONLY, 0666);
	ptr = (char*)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
	printf("%s\n",(char*)ptr);
	shm_unlink(name);
	return 0;
}

void shm()
{
	pid_t pid;
	pid = fork();
	
	if(pid < 0){
		fprintf(stderr,"Fork Failed");
		exit(1);
	}
	
	else if(pid == 0){
		printf("child process is working ...\n");
		consumer();
		exit(0);
	}
	
	else{
		printf("parents process is working ...\n");
		producer();
	}
}
	
	
	
	
	
	
	
	
	



			      
