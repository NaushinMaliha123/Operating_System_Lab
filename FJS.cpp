#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, i, j;
    int bt[20], wt[20], tat[20], p[20];
    float avg_wt = 0, avg_tat = 0;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter burst time:\n";

    for(i = 0; i < n; i++)
    {
        p[i] = i + 1;
        cout << "P" << i + 1 << ": ";
        cin >> bt[i];
    }

    // Sort according to burst time
    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(bt[i] > bt[j])
            {
                swap(bt[i], bt[j]);
                swap(p[i], p[j]);
            }
        }
    }

    // Gantt Chart
    cout << "\nGantt Chart:\n|";

    for(i = 0; i < n; i++)
    {
        cout << " P" << p[i] << " |";
    }

    cout << "\n0";

    int time = 0;

    for(i = 0; i < n; i++)
    {
        time += bt[i];
        cout << "\t" << time;
    }

    cout << "\n";

    // Waiting Time
    wt[0] = 0;

    for(i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    // Turnaround Time
    for(i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt[i];
    }

    // Display Table
    cout << "\nProcess\tBT\tWT\tTAT\n";

    for(i = 0; i < n; i++)
    {
        cout << "P" << p[i] << "\t"
             << bt[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << "\n";

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    // Average
    avg_wt /= n;
    avg_tat /= n;

    cout << fixed << setprecision(2);

    cout << "\nAverage Waiting Time = " << avg_wt;
    cout << "\nAverage Turnaround Time = " << avg_tat << endl;

    return 0;
}