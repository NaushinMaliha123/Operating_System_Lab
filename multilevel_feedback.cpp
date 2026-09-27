#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int bt[n], rt[n], q[n];
    int ct[n], wt[n], tat[n], response[n];
    bool started[n] = {};

    // Input
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Burst Time for P" << i + 1 << ": ";
        cin >> bt[i];

        rt[i] = bt[i];
        q[i] = 1;   // All processes start in Queue 1
    }

    int time = 0, completed = 0;

    // Gantt Chart
    int gp[1000], gs[1000], ge[1000];
    int g = 0;

    while (completed < n)
    {
        bool found = false;

        // Queue 1 -> Round Robin, Quantum = 4
        for (int i = 0; i < n; i++)
        {
            if (q[i] == 1 && rt[i] > 0)
            {
                found = true;

                if (!started[i])
                {
                    response[i] = time;
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
                else
                {
                    q[i] = 2;   // Move to Queue 2
                }
            }
        }

        // Queue 2 -> Round Robin, Quantum = 8
        for (int i = 0; i < n; i++)
        {
            if (q[i] == 2 && rt[i] > 0)
            {
                found = true;

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
                else
                {
                    q[i] = 3;   // Move to Queue 3
                }
            }
        }

        // Queue 3 -> FCFS
        for (int i = 0; i < n; i++)
        {
            if (q[i] == 3 && rt[i] > 0)
            {
                found = true;

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

        if (!found)
            time++;
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
        tat[i] = ct[i];
        wt[i] = tat[i] - bt[i];
    }

    // Display Result
    cout << "\nProcess\tBT\tCT\tWT\tTAT\tRT\n";

    double totalWT = 0, totalTAT = 0, totalRT = 0;

    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << "\t"
             << bt[i] << "\t"
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

