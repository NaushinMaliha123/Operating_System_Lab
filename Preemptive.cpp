#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n], rt[n], pr[n];
    int ct[n], wt[n], tat[n];

    // Input
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Arrival Time for P" << i + 1 << ": ";
        cin >> at[i];

        cout << "Enter Burst Time for P" << i + 1 << ": ";
        cin >> bt[i];

        cout << "Enter Priority for P" << i + 1 << ": ";
        cin >> pr[i];

        rt[i] = bt[i];
    }

    int completed = 0, time = 0;

    // Gantt Chart arrays
    int gp[1000], start[1000], finish[1000];
    int g = 0;

    while (completed < n)
    {
        int highest = -1;
        int bestPriority = INT_MAX;

        // Find highest priority process
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && rt[i] > 0)
            {
                if (pr[i] < bestPriority)
                {
                    bestPriority = pr[i];
                    highest = i;
                }
            }
        }

        // CPU Idle
        if (highest == -1)
        {
            time++;
            continue;
        }

        // Store Gantt Chart
        if (g == 0 || gp[g - 1] != highest)
        {
            gp[g] = highest;
            start[g] = time;
            g++;
        }

        // Execute for 1 unit
        rt[highest]--;
        time++;

        // Update finish time
        finish[g - 1] = time;

        // Process finishes
        if (rt[highest] == 0)
        {
            completed++;

            ct[highest] = time;
            tat[highest] = ct[highest] - at[highest];
            wt[highest] = tat[highest] - bt[highest];
        }
    }

    // Gantt Chart
    cout << "\nGantt Chart:\n|";

    for (int i = 0; i < g; i++)
    {
        cout << " P" << gp[i] + 1 << " |";
    }

    cout << "\n" << start[0];

    for (int i = 0; i < g; i++)
    {
        cout << "\t" << finish[i];
    }

    cout << "\n";

    // Display Results
    cout << "\nProcess\tAT\tBT\tPR\tCT\tWT\tTAT\n";

    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << pr[i] << "\t"
             << ct[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << endl;
    }

    return 0;
}