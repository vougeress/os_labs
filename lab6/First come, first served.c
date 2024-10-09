#include <stdio.h>

int main() {
   int n;
    scanf("%d", &n);
    int burst_time[n], waiting_time[n], turnaround_time[n];
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &burst_time[i]);
    }
    waiting_time[0] = 0;
    for (int i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + burst_time[i - 1];
        total_wt += waiting_time[i];
    }
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
        total_tat += turnaround_time[i];
    }
    printf("\nProcess  Burst Time  Waiting Time  Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("   %d         %d           %d               %d\n", i + 1, burst_time[i], waiting_time[i], turnaround_time[i]);
    }


}
