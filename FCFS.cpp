#include<iostream>
using namespace std;

// Function to find the waiting time for all processes
void findWaitingTime(int processes[], int n, int bt[], int at[], int wt[])
{
    wt[0] = 0;  // waiting time for the first process is 0

    // calculating waiting time for each process
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i-1] + wt[i-1];  // waiting time = previous process's waiting time + burst time of the previous process
    }
}

// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[])
{
    // calculating turnaround time by adding burst time and waiting time
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];  // turnaround time = burst time + waiting time
    }
}

// Function to calculate completion time for all processes
void findCompletionTime(int processes[], int n, int bt[], int at[], int ct[])
{
    int start_time = 0;  // Initially, the start time is 0

    // calculating completion time for each process
    for (int i = 0; i < n; i++) {
        start_time = (i == 0) ? at[i] : max(at[i], start_time);  // Ensure that process starts at arrival time
        ct[i] = start_time + bt[i];  // completion time = start time + burst time
        start_time = ct[i];  // Update start time for the next process
    }
}

// Function to calculate average times
void findavgTime(int processes[], int n, int bt[], int at[])
{
    int wt[n], tat[n], ct[n], total_wt = 0, total_tat = 0;

    // Find waiting time for all processes
    findWaitingTime(processes, n, bt, at, wt);

    // Find turnaround time for all processes
    findTurnAroundTime(processes, n, bt, wt, tat);

    // Find completion time for all processes
    findCompletionTime(processes, n, bt, at, ct);

    // Display process details
    cout << "Processes  " << "Arrival Time  " << "Burst Time  "
         << "Waiting Time  " << "Turnaround Time  " << "Completion Time\n";

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << "   " << i + 1 << "\t\t" << at[i] << "\t\t"
             << bt[i] << "\t\t" << wt[i] << "\t\t  " << tat[i] << "\t\t  " << ct[i] << endl;
    }

    // Display average waiting time and average turnaround time
    cout << "Average waiting time = " << (float)total_wt / (float)n << endl;
    cout << "Average turnaround time = " << (float)total_tat / (float)n << endl;
}

// Driver code
int main()
{
    // Process ids
    int processes[] = {1, 2, 3};
    int n = sizeof(processes) / sizeof(processes[0]);

    // Arrival time of all processes
    int arrival_time[] = {0, 1, 2};

    // Burst time of all processes
    int burst_time[] = {10, 5, 8};

    // Function call to find average times
    findavgTime(processes, n, burst_time, arrival_time);
    return 0;
}
