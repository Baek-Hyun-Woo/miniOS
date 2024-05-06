#include <stdio.h>

#define MAX_PROCESSES 20

typedef struct {
  int pid;
  int burst_time;
  int remaining_time;
} Process;

Process processes[MAX_PROCESSES];
int num_processes;

void schedule() {
  int current_time = 0;
  int completed_processes = 0;
  int quantum;

  printf("Enter the time quantum: ");
  scanf("%d", &quantum);
  printf("\n");

  while (completed_processes < num_processes) {
    for (int i = 0; i < num_processes; i++) {
      if (processes[i].remaining_time > 0) {
        int execution_time = (processes[i].remaining_time > quantum) ? quantum : processes[i].remaining_time;
        processes[i].remaining_time -= execution_time;
        current_time += execution_time;

        printf("Process %d executed for %d units. Remaining time: %d\n", processes[i].pid, execution_time, processes[i].remaining_time);

        if (processes[i].remaining_time == 0) {
          completed_processes++;
          printf("Process %d completed at time %d\n\n", processes[i].pid, current_time);
        }
      }
    }
  }
}

int round_robin() {
  printf("Enter the number of processes: ");
  scanf("%d", &num_processes);
  printf("\n");

  for (int i = 0; i < num_processes; i++) {
    processes[i].pid = i + 1;
    printf("Enter burst time for process %d: ", i + 1);
    scanf("%d", &processes[i].burst_time);
    processes[i].remaining_time = processes[i].burst_time;
  }

  schedule();

  return 0;
}

