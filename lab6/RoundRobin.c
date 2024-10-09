#include <stdio.h>

int main() {
    int n, quantum, t = 0;
    scanf("%d", &n);
    scanf("%d", &quantum);

    int burst_time[n], rem_bt[n], waiting_time[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &burst_time[i]);
        rem_bt[i] = burst_time[i];
        waiting_time[i] = 0;
    }
    int completed_processes = 0;
    while (completed_processes < n) {
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    t += rem_bt[i];
                    waiting_time[i] = t - burst_time[i];
                    rem_bt[i] = 0;
                    completed_processes++;
                }
                printf("Time %d: Process %d is executing\n", t, i + 1);
            }
        }
    }
    printf("\nWaiting times for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: %d\n", i + 1, waiting_time[i]);
    }
    return 0;
}
