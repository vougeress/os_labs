#include <stdio.h>
#include <stdbool.h>

int findNextProcess(int n, int arrival_time[], int burst_time[], bool completed[], int current_time) {
    int shortest_job_index = -1;
    int min_burst_time = 100000;

    for (int i = 0; i < n; i++) {
        if (arrival_time[i] <= current_time && !completed[i] && burst_time[i] < min_burst_time) {
            min_burst_time = burst_time[i];
            shortest_job_index = i;
        }
    }
    return shortest_job_index;
}

int main() {
    int n;
    scanf("%d", &n);

    int arrival_time[n], burst_time[n];
    bool completed[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &arrival_time[i], &burst_time[i]);
        completed[i] = false;
    }

    int current_time = 0, completed_processes = 0;

    while (completed_processes < n) {
        int next_proc_index = findNextProcess(n, arrival_time, burst_time, completed, current_time);
        if (next_proc_index == -1) {
            current_time++;
        } else {
            printf("Time %d: Process %d is executing (Burst time: %d)\n", current_time, next_proc_index + 1, burst_time[next_proc_index]);
            current_time += burst_time[next_proc_index];
            completed[next_proc_index] = true;
            completed_processes++;
        }
    }

    printf("All processes completed.\n");
    return 0;
}
