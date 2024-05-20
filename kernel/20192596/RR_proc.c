#include <stdio.h>

#define MAX_PROCESSES 20

typedef enum { READY, RUNNING, WAITING, TERMINATED } ProcessState;

typedef struct {
  int pid;
  int burst_time;
  int remaining_time;
  int io_time;
  ProcessState state;
} Process;

Process processes[MAX_PROCESSES];
int num_processes;

void schedule2() {
  int current_time = 0;
  int completed_processes = 0;
  int quantum;

  printf("Enter the time quantum: ");
  scanf("%d", &quantum);
  printf("\n");

  // Initialize all processes to READY state
  for (int i = 0; i < num_processes; i++) {
    processes[i].state = READY;
  }

  // Create a queue to store the processes
  int queue[MAX_PROCESSES];
  int front = 0, rear = 0;
  for (int i = 0; i < num_processes; i++) {
    queue[rear++] = i;
  }

  while (completed_processes < num_processes) {
    if (front == rear) { // 큐가 비어있으면 종료
      break;
    }

    int current_process = queue[front]; 

    // Check if the current process is READY
    if (processes[current_process].state == READY) {
      if (processes[current_process].remaining_time > 0) {
        int execution_time = (processes[current_process].remaining_time > quantum) ? quantum : processes[current_process].remaining_time;
        processes[current_process].remaining_time -= execution_time;
        current_time += execution_time;

        printf("Process %d executed for %d units. Remaining time: %d\n", processes[current_process].pid, execution_time, processes[current_process].remaining_time);

        // If process completes, move it to TERMINATED state
        if (processes[current_process].remaining_time == 0) {
          completed_processes++;
          printf("Process %d completed at time %d\n\n", processes[current_process].pid, current_time);
          processes[current_process].state = TERMINATED;
        } else {
          // If process needs I/O, move it to WAITING state
          if (processes[current_process].io_time > 0) {
            processes[current_process].state = WAITING;
            printf("Process %d moved to WAITING state for I/O\n", processes[current_process].pid);
          }
        }
      } else {
        // If the process has no remaining time, move it to TERMINATED state
        processes[current_process].state = TERMINATED;
        completed_processes++;
        printf("Process %d completed at time %d\n\n", processes[current_process].pid, current_time);
      }
    } else if (processes[current_process].state == WAITING) {
      // If the process is WAITING, decrease its I/O time
      processes[current_process].io_time--;
      if (processes[current_process].io_time == 0) {
        // After I/O, move the process back to READY state
        processes[current_process].state = READY;
        printf("Process %d moved back to READY state\n", processes[current_process].pid);
      }
    }

    // Move the current process to the end of the queue
    if (rear < MAX_PROCESSES) { // rear가 MAX_PROCESSES를 넘지 않도록 확인
        queue[rear] = queue[front];
        rear = (rear + 1) % MAX_PROCESSES; // rear를 늘리고, MAX_PROCESSES로 나눈 나머지를 사용하여 원형 큐를 구현
    }
    front = (front + 1) % MAX_PROCESSES; // front를 늘리고, MAX_PROCESSES로 나눈 나머지를 사용하여 원형 큐를 구현
  }
}

int RR() {
  printf("Enter the number of processes: ");
  scanf("%d", &num_processes);

  // num_processes가 MAX_PROCESSES를 초과하는 경우 오류 처리
  if (num_processes > MAX_PROCESSES) {
    printf("Error: The number of processes exceeds the maximum limit.\n");
    return 1; 
  }

  printf("\n");

  for (int i = 0; i < num_processes; i++) {
    processes[i].pid = i + 1;
    printf("Enter burst time for process %d: ", i + 1);
    scanf("%d", &processes[i].burst_time);
    processes[i].remaining_time = processes[i].burst_time;

    // Remove priority input
    printf("Enter I/O time for process %d: ", i + 1);
    scanf("%d", &processes[i].io_time);
  }

  schedule2();

  return 0;
}
