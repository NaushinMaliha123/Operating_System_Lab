#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, tq;

    cout << "Enter number of processes: ";
    cin >> n;

    int bt[n], rt[n], wt[n], tat[n], ct[n];

    // Input Burst Time
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Burst Time for P" << i + 1 << ": ";
        cin >> bt[i];
        rt[i] = bt[i];
    }

    cout << "Enter Time Quantum: ";
    cin >> tq;

    int time = 0, done;

    // Gantt Chart arrays
    int gp[100], start[100], finish[100];
    int g = 0;

    // Round Robin
    do
    {
        done = 1;

        for (int i = 0; i < n; i++)
        {
            if (rt[i] > 0)
            {
                done = 0;

                gp[g] = i;
                start[g] = time;

                if (rt[i] > tq)
                {
                    time += tq;
                    rt[i] -= tq;
                }
                else
                {
                    time += rt[i];
                    rt[i] = 0;
                    ct[i] = time;
                }

                finish[g] = time;
                g++;
            }
        }

    } while (!done);

    // Gantt Chart
    cout << "\nGantt Chart:\n|";

    for (int i = 0; i < g; i++)
        cout << " P" << gp[i] + 1 << " |";

    cout << "\n" << start[0];

    for (int i = 0; i < g; i++)
        cout << "\t" << finish[i];

    cout << "\n";

    // Calculate WT and TAT
    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i];       // AT = 0
        wt[i] = tat[i] - bt[i];
    }

    // Display Table
    cout << "\nProcess\tBT\tCT\tWT\tTAT\n";

    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << "\t"
             << bt[i] << "\t"
             << ct[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << endl;
    }

    return 0;
}