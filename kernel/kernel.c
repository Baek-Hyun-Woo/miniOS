#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "system.h"
void print_minios(char* str);

int main() {
    print_minios("[MiniOS SSU] Hello, World!");

    char *input;

    while(1) {
        // readline을 사용하여 입력 받기
        input = readline("커맨드를 입력하세요(종료:exit) : ");

        if (strcmp(input,"exit") == 0) {
            break;
        }

        else if (strcmp(input,"minisystem") == 0){
            minisystem();
        }
        
        else if (strcmp(input,"student_id") == 0){
            student_id();
        }
        else if (strcmp(input,"shm") == 0){
            shm();
        }
        else if (strcmp(input,"pipe") == 0){
            ipc_pipe();
        }
	    else if (strcmp(input,"pi") == 0){
	        pi();
	    }
        else if (strcmp(input,"roundrobin") == 0){
            round_robin();
        }
        else if (strcmp(input,"minils")==0){
            minils();
        }
        else if (strcmp(input,"sync") == 0){
            sync_cal_pi();
        }
        else if (strcmp(input,"RR") == 0){
            RR();
        }
        else system(input);
    }

    // 메모리 해제
    free(input);
    print_minios("[MiniOS SSU] MiniOS Shutdown........");

    return(1);
}

void print_minios(char* str) {
        printf("%s\n",str);
}
