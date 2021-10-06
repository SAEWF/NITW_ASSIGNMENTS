#include <iostream>
#include <queue>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;
struct FCFS
{
    bool operator()(const vector<int> &a, const vector<int> &b)
    {
        return a[1] > b[1];
    }
};
struct SFJNP
{
    bool operator()(const vector<int> &a, const vector<int> &b)
    {
        if (a[2] == b[2])
            return a[1] > b[1];
        return a[2] > b[2];
    }
};
vector<vector<int>> schedule;
void SFJP(priority_queue<vector<int>, vector<vector<int>>, FCFS> &pq)
{
    int time = 0, waitingTime = 0, size = pq.size();
    priority_queue<vector<int>, vector<vector<int>>, SFJNP> temp;
    cout << "Gantt Chart-> ";
    while (!(pq.empty() && temp.empty()))
    {

        while (time >= pq.top()[1])
        {
            temp.push(pq.top());
            pq.pop();
        }
        if (!temp.empty())
        {
            auto t = temp.top();
            temp.pop();
            t[3] = min(t[3], time);

            cout << t[0] << " ";
            t[2] -= 1;
            if (t[2] != 0)
                temp.push(t);
            else
            {
                t[4] = time + 1;
                schedule.push_back(t);
                waitingTime += time - t[3] + 1;
            }
        }
        else
        {
            cout << "N ";
        }
        time += 1;
    }
    cout << "\nAverage Waiting time-> " << (float)(((float)waitingTime) / size) << "\n";
    cout << "Total Completion time->" << time << "\n";
}
void print()
{
    cout << "Process ID\tArrival Time\tBurst Time\tStart Time\tCompletion Time\tTurn Around time\tWaiting Time\n";
    for (auto i : schedule)
    {
        for (auto j : i)
        {
            cout << j << "\t\t";
        }
        cout << i[4] - i[1] << "\t\t\t" << i[3] - i[1] << "\n";
    }
}
int main()
{
    priority_queue<vector<int>, vector<vector<int>>, FCFS> pq;
    int totalProcesses;
    cout << "Enter number of processes-> ";
    cin >> totalProcesses;
    for (int i = 0; i < totalProcesses; i++)
    {
        cout << "Enter process ID, Arrival Time, Burst time:- ";
        int pid, arr, burst;
        cin >> pid >> arr >> burst;
        pq.push({pid, arr, burst, INT32_MAX, INT32_MAX});
    }
    SFJP(pq);
    print();
}