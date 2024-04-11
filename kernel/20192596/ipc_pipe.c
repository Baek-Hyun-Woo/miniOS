#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int ipc_pipe()
{
	char write_msg[BUFFER_SIZE] = "Greetings";
	char read_msg[BUFFER_SIZE];
	int fd[2];
	pid_t pid;
	if(pipe(fd) == -1){
		fprintf(stderr, " Pipe failed \n");
	return 1;
	}

	pid = fork();
	if(pid < 0){
		fprintf(stderr, "Fork Failed \n");
		return 1;
	}
	else if(pid > 0){ //parent process
		close(fd[READ_END]);
		write(fd[WRITE_END], write_msg, strlen(write_msg)+1);
		close(fd[WRITE_END]);
		wait(NULL);
	}
	else{ //child process
		close(fd[WRITE_END]);
		read(fd[READ_END], read_msg, BUFFER_SIZE);
		printf("Read : [%s]\n",read_msg);
		close(fd[READ_END]);
		exit(0);
	}
	return 0;
}
