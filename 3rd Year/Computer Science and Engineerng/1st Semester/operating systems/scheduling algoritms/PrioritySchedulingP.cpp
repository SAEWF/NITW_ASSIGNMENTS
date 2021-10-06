//Priority Scheduling Premptive CPP implemenation

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
void prioritySchedulingP(priority_queue<vector<int>, vector<vector<int>>, FCFS> &pq)
{
    int time = 0, waitingTime = 0, size = pq.size();
    priority_queue<vector<int>, vector<vector<int>>, priority> temp;
    cout << "Gantt chart-> ";
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
            t[4] = min(t[4], time);
            cout << t[0] << " ";
            t[2] -= 1;
            if (t[2] != 0)
            {
                temp.push(t);
            }
            else
            {
                t[5] = time + 1;
                schedule.push_back(t);
                waitingTime += time - t[4] + 1;
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
        pq.push({pid, arr, burst, prio, INT32_MAX, INT32_MAX});
    }
    prioritySchedulingP(pq);
    print();
}
