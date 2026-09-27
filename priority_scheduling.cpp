#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n, i, j;
    int bt[20], wt[20], tat[20], p[20], priority[20];

    float avg_wt = 0, avg_tat = 0;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter burst time and priority:\n";

    for(i = 0; i < n; i++)
    {
        p[i] = i + 1;

        cout << "\nP" << i + 1 << endl;

        cout << "Burst Time: ";
        cin >> bt[i];

        cout << "Priority: ";
        cin >> priority[i];
    }

    // Sort according to priority
    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(priority[i] > priority[j])
            {
                swap(priority[i], priority[j]);
                swap(bt[i], bt[j]);
                swap(p[i], p[j]);
            }
        }
    }

    // Gantt Chart
    cout << "\nGantt Chart:\n";

    cout << " ";

    for(i = 0; i < n; i++)
    {
        cout << "--------";
    }

    cout << "\n|";

    for(i = 0; i < n; i++)
    {
        cout << "  P" << p[i] << "   |";
    }

    cout << "\n ";

    for(i = 0; i < n; i++)
    {
        cout << "--------";
    }

    cout << "\n0";

    int time = 0;

    for(i = 0; i < n; i++)
    {
        time = time + bt[i];
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
    cout << "\nProcess\tBT\tPriority\tWT\tTAT\n";

    for(i = 0; i < n; i++)
    {
        cout << "P" << p[i] << "\t"
             << bt[i] << "\t"
             << priority[i] << "\t\t"
             << wt[i] << "\t"
             << tat[i] << endl;

        avg_wt += wt[i];
        avg_tat += tat[i];
    }


    // Average
    avg_wt = avg_wt / n;
    avg_tat = avg_tat / n;

    cout << fixed << setprecision(2);

    cout << "\nAverage Waiting Time = " << avg_wt;
    cout << "\nAverage Turnaround Time = " << avg_tat << endl;

    return 0;
}