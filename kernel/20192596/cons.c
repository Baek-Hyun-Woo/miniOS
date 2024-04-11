#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int cons()
{
	
	const int SIZE = 4096; // size of shared memory
	const char *name = "OS"; // name of shared memory object
	int fd;
	char *ptr;
	fd = shm_open(name, O_RDONLY, 0666);
	ptr = (char*)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	printf("%s",(char*)ptr);
	shm_unlink(name);
	return 0;
}
