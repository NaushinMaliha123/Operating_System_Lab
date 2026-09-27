#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n], rt[n], ct[n], wt[n], tat[n];

    // Gantt Chart data
    int gantt[1000], gtime[1000];
    int g = 0;

    // Input
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Arrival Time for P" << i + 1 << ": ";
        cin >> at[i];

        cout << "Enter Burst Time for P" << i + 1 << ": ";
        cin >> bt[i];

        rt[i] = bt[i];
    }

    int completed = 0, currentTime = 0;

    while (completed < n)
    {
        int shortest = -1;
        int minTime = INT_MAX;

        // Find shortest remaining time
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= currentTime && rt[i] > 0 && rt[i] < minTime)
            {
                minTime = rt[i];
                shortest = i;
            }
        }

        // No process available
        if (shortest == -1)
        {
            currentTime++;
            continue;
        }

        // Store Gantt Chart
        if (g == 0 || gantt[g - 1] != shortest)
        {
            gantt[g] = shortest;
            gtime[g] = currentTime;
            g++;
        }

        // Execute for 1 unit
        rt[shortest]--;
        currentTime++;

        // Process completed
        if (rt[shortest] == 0)
        {
            completed++;

            ct[shortest] = currentTime;
            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];
        }
    }

    // Gantt Chart
    cout << "\nGantt Chart:\n|";

    for (int i = 0; i < g; i++)
        cout << " P" << gantt[i] + 1 << " |";

    cout << "\n" << gtime[0];

    for (int i = 1; i < g; i++)
        cout << "\t" << gtime[i];

    cout << "\t" << currentTime << "\n";

    // Results
    cout << "\nProcess\tAT\tBT\tCT\tWT\tTAT\n";

    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << ct[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << endl;
    }

    return 0;
}