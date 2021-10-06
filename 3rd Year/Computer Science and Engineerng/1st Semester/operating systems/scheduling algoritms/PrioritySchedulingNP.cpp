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
struct priority
{
    bool operator()(const vector<int> &a, const vector<int> &b)
    {
        if (a[3] == b[3])
            return a[1] > b[1];
        return a[3] > b[3];
    }
};
vector<vector<int>> schedule;
void priorityScheduling(priority_queue<vector<int>, vector<vector<int>>, FCFS> &pq)
{
    int time = 0, waitingTime = 0, size = pq.size();
    priority_queue<vector<int>, vector<vector<int>>, priority> temp;
    cout << "Gantt Chart-> ";
    while (!(temp.empty() && pq.empty()))
    {
        while (!pq.empty() && time >= pq.top()[1])
        {
            temp.push(pq.top());
            pq.pop();
        }
        if (temp.empty())
        {
            while(time!=temp.top()[1])
            {
                cout << "N ";
                time += 1;
            }
        }
        auto t = temp.top();
        temp.pop();
        time = max(time, t[1]);
        schedule.push_back({t[0], t[1], t[2], t[3], time, time + t[2]});
        waitingTime += (time - t[1]);
        time += t[2];
    }
    cout << "\nAverage Waiting time-> " << (float)(((float)waitingTime) / size) << "\n";
    cout << "Total Completion time->" << time << "\n";
}
void print()
{
    cout << "Process ID\tArrival Time\tBurst Time\tPriority\tStart Time\tCompletion Time\tTurn Around time\tWaiting Time\n";
    for (auto i : schedule)
    {
        for (auto j : i)
        {
            cout << j << "\t\t";
        }
        cout << i[5] - i[1] << "\t\t\t" << i[4] - i[1] << "\n";
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
        cout << "Enter process ID, Arrival Time, Burst time, Priority:- ";
        int pid, arr, burst, prio;
        cin >> pid >> arr >> burst >> prio;
        pq.push({pid, arr, burst, prio});
    }
    priorityScheduling(pq);
    print();
}