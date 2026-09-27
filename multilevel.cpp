#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n], rt[n], q[n];
    int ct[n], wt[n], tat[n], response[n];
    bool started[n] = {};

    for (int i = 0; i < n; i++)
    {
        cout << "\nP" << i + 1 << ":\n";

        cout << "Arrival Time: ";
        cin >> at[i];

        cout << "Burst Time: ";
        cin >> bt[i];

        cout << "Queue (1=RR4, 2=RR8, 3=FCFS): ";
        cin >> q[i];

        rt[i] = bt[i];
    }

    int time = 0, completed = 0;

    // Gantt Chart
    int gp[1000], gs[1000], ge[1000];
    int g = 0;

    while (completed < n)
    {
        int selected = -1;

        // Find highest priority ready queue
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && rt[i] > 0)
            {
                if (selected == -1 || q[i] < q[selected])
                    selected = i;
            }
        }

        // CPU idle
        if (selected == -1)
        {
            time++;
            continue;
        }

        // Queue 1 - Round Robin (Quantum = 4)
        if (q[selected] == 1)
        {
            for (int i = 0; i < n; i++)
            {
                if (q[i] == 1 && at[i] <= time && rt[i] > 0)
                {
                    if (!started[i])
                    {
                        response[i] = time - at[i];
                        started[i] = true;
                    }

                    gp[g] = i;
                    gs[g] = time;

                    int run = min(4, rt[i]);
                    time += run;
                    rt[i] -= run;

                    ge[g] = time;
                    g++;

                    if (rt[i] == 0)
                    {
                        ct[i] = time;
                        completed++;
                    }
                }
            }
        }

        // Queue 2 - Round Robin (Quantum = 8)
        else if (q[selected] == 2)
        {
            for (int i = 0; i < n; i++)
            {
                if (q[i] == 2 && at[i] <= time && rt[i] > 0)
                {
                    if (!started[i])
                    {
                        response[i] = time - at[i];
                        started[i] = true;
                    }

                    gp[g] = i;
                    gs[g] = time;

                    int run = min(8, rt[i]);
                    time += run;
                    rt[i] -= run;

                    ge[g] = time;
                    g++;

                    if (rt[i] == 0)
                    {
                        ct[i] = time;
                        completed++;
                    }
                }
            }
        }

        // Queue 3 - FCFS
        else
        {
            int i = selected;

            if (!started[i])
            {
                response[i] = time - at[i];
                started[i] = true;
            }

            gp[g] = i;
            gs[g] = time;

            time += rt[i];
            rt[i] = 0;

            ge[g] = time;
            g++;

            ct[i] = time;
            completed++;
        }
    }

    // Gantt Chart
    cout << "\nGantt Chart:\n|";

    for (int i = 0; i < g; i++)
        cout << " P" << gp[i] + 1 << " |";

    cout << "\n" << gs[0];

    for (int i = 0; i < g; i++)
        cout << "\t" << ge[i];

    cout << "\n";

    // Calculate WT and TAT
    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    // Display table
    cout << "\nProcess\tAT\tBT\tQueue\tCT\tWT\tTAT\tRT\n";

    double totalWT = 0, totalTAT = 0, totalRT = 0;

    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << q[i] << "\t"
             << ct[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << "\t"
             << response[i] << "\n";

        totalWT += wt[i];
        totalTAT += tat[i];
        totalRT += response[i];
    }

    cout << fixed << setprecision(2);

    cout << "\nAverage Waiting Time = " << totalWT / n;
    cout << "\nAverage Turnaround Time = " << totalTAT / n;
    cout << "\nAverage Response Time = " << totalRT / n << endl;

    return 0;
}