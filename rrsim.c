#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

#define MAX_BUFFER_LEN 80

taskval_t *event_list = NULL;

int average_wait = 0;
int average_tat = 0;

void print_task(taskval_t *t, void *arg) {
    printf("task %03d: %5d %3.2f %3.2f\n",
        t->id,
        t->arrival_time,
        t->cpu_request,
        t->cpu_used
    );
}


void increment_count(taskval_t *t, void *arg) {
    int *ip;
    ip = (int *)arg;
    (*ip)++;
}

//Tim Rolston #V00920780
void run_simulation(int qlen, int dlen) {

    taskval_t *ready_q = NULL;
    taskval_t *temp = NULL;
    taskval_t *next_event = NULL;
    float wait_time;
    int tick_quantum = 0, tick_dispatch, tick_number = 0, tat;
    int progress = 0;
    int number_task = 0;

    if (event_list != NULL){
      apply(event_list, increment_count, &number_task);
    }

    if (qlen == 0){
      fprintf(stderr, "Cannot compute tasks with 0 quantum\n");
      exit(1);
    }

    while (event_list != NULL || ready_q != NULL){

        if (event_list != NULL){
        next_event = peek_front(event_list);
      }
      if (tick_number != next_event->arrival_time && ready_q == NULL){
        printf("[%05d] IDLE\n", tick_number);
        tick_number++;
        continue;
      }
//add onto ready queue from event list
      if ((tick_number >= next_event->arrival_time) && (event_list != NULL)){
        event_list = remove_front(event_list);
        ready_q = add_end(ready_q, next_event);

      }
//check if task is in progress
      if (progress == 0){
        tick_dispatch = 0;
        progress = 1;
        temp = peek_front(ready_q);
        tick_quantum = 0;
      }
//check whether or not to increment tick count for dispatch
      if ((dlen == 0)){
        if(tick_dispatch == 0){
          tick_dispatch++;
          printf("[%05d] DISPATCHING\n", tick_number);
        }
      }
      else{
        if (tick_dispatch != dlen){
          tick_dispatch++;
          printf("[%05d] DISPATCHING\n", tick_number);
          tick_number++;
          continue;
        }
      }

      temp = peek_front(ready_q);
      if (temp->cpu_used < temp->cpu_request){
        if (tick_quantum != qlen){
          printf("[%05d] id=%05d req=%.2f used=%.2f\n", tick_number,
          temp->id, temp->cpu_request, temp->cpu_used);
          tick_quantum++;
          tick_number++;
          temp->cpu_used = temp->cpu_used + 1;
          continue;
        }
        ready_q = add_end(remove_front(ready_q), ready_q);
      }
//task has completed.
      else{
        tat = tick_number - temp->arrival_time;
        wait_time = (float)tat - temp->cpu_request;
        printf("[%05d] id=%05d EXIT w=%.2f ta=%.2f\n", tick_number,
        temp->id, (float)wait_time, (float)tat );
        average_wait += wait_time;
        average_tat += tat;
        ready_q = remove_front(ready_q);
      }
    progress = 0;
    continue;
  }
//---Uncomment section and comment out ALL other print statements for graph data creation
/*  average_wait = average_wait / number_task;
  average_tat = average_tat / number_task;
  printf("%d,%d\n", average_wait, average_tat);*/
//-------------------------------------------------
}


int main(int argc, char *argv[]) {
    char   input_line[MAX_BUFFER_LEN];
    int    i;
    int    task_num;
    int    task_arrival;
    float  task_cpu;
    int    quantum_length = -1;
    int    dispatch_length = -1;

    taskval_t *temp_task;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--quantum") == 0 && i+1 < argc) {
            quantum_length = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i], "--dispatch") == 0 && i+1 < argc) {
            dispatch_length = atoi(argv[i+1]);
        }
    }

    if (quantum_length == -1 || dispatch_length == -1) {
        fprintf(stderr,
            "usage: %s --quantum <num> --dispatch <num>\n",
            argv[0]);
        exit(1);
    }


    while(fgets(input_line, MAX_BUFFER_LEN, stdin)) {
        sscanf(input_line, "%d %d %f", &task_num, &task_arrival,
            &task_cpu);
        temp_task = new_task();
        temp_task->id = task_num;
        temp_task->arrival_time = task_arrival;
        temp_task->cpu_request = task_cpu;
        temp_task->cpu_used = 0.0;
        event_list = add_end(event_list, temp_task);
    }

#ifdef DEBUG
    int num_events;
    apply(event_list, increment_count, &num_events);
    printf("DEBUG: # of events read into list -- %d\n", num_events);
    printf("DEBUG: value of quantum length -- %d\n", quantum_length);
    printf("DEBUG: value of dispatch length -- %d\n", dispatch_length);
#endif

    run_simulation(quantum_length, dispatch_length);

    return (0);
}
