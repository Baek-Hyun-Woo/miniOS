#include <stdio.h>

#define MAX_PROCESSES 20

typedef enum { READY, RUNNING, TERMINATED } ProcessState;

typedef struct {
  int pid;
  int burst_time;
  int remaining_time;
  ProcessState state;
} Process;

Process processes[MAX_PROCESSES];
int num_processes;

void print_process_state(int pid, ProcessState state) {
  const char* state_str;
  switch(state) {
    case READY: state_str = "READY"; break;
    case RUNNING: state_str = "RUNNING"; break;
    case TERMINATED: state_str = "TERMINATED"; break;
    default: state_str = "UNKNOWN"; break;
  }
  printf("Process %d is in %s state.\n", pid, state_str);
}

void schedule2() {
  int current_time = 0;
  int completed_processes = 0;
  int quantum;

  printf("Enter the time quantum: ");
  scanf("%d", &quantum);
  printf("\n");

  // Initialize 
  for (int i = 0; i < num_processes; i++) {
    processes[i].state = READY;
    print_process_state(processes[i].pid, processes[i].state);
  }

  printf("\n");

  // queue of process
  int queue[MAX_PROCESSES];
  int front = 0, rear = 0;
  for (int i = 0; i < num_processes; i++) {
    queue[rear++] = i;
  }

  while (completed_processes < num_processes) {
    if (front == rear) { //empty
      break;
    }

    int current_process = queue[front]; 

    // READY -> RUNNING
    if (processes[current_process].state == READY) {
      processes[current_process].state = RUNNING;
      print_process_state(processes[current_process].pid, processes[current_process].state);

      if (processes[current_process].remaining_time > 0) {
        int execution_time = (processes[current_process].remaining_time > quantum) ? quantum : processes[current_process].remaining_time;
        processes[current_process].remaining_time -= execution_time;
        current_time += execution_time;

        printf("Process %d executed for %d units. Remaining time: %d\n", processes[current_process].pid, execution_time, processes[current_process].remaining_time);

        // RUNNING -> TERMINATED
        if (processes[current_process].remaining_time == 0) {
          processes[current_process].state = TERMINATED;
          completed_processes++;
          printf("Process %d completed at time %d\n", processes[current_process].pid, current_time);
          print_process_state(processes[current_process].pid, processes[current_process].state);
          printf("\n");
        } else { //RUNNING -> READY
          processes[current_process].state = READY;
          print_process_state(processes[current_process].pid, processes[current_process].state);
          printf("\n");
        }
      }
    }

    // queue update
    if (rear < MAX_PROCESSES) { 
      queue[rear] = queue[front];
      rear = (rear + 1) % MAX_PROCESSES; 
    }
    front = (front + 1) % MAX_PROCESSES;
  }
}

int RR() {
  printf("Enter the number of processes: ");
  scanf("%d", &num_processes);

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
  }

  schedule2();

  return 0;
}
