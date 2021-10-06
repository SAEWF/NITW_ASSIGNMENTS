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
vector<vector<int>> schedule;
struct SFJNP
{
    bool operator()(const vector<int> &a, const vector<int> &b)
    {
        if (a[2] == b[2])
            return a[1] > b[1];
        return a[2] > b[2];
    }
};
void SFJNPscheduling(priority_queue<vector<int>, vector<vector<int>>, FCFS> &pq)
{
    int time = 0, waitingTime = 0;
    priority_queue<vector<int>, vector<vector<int>>, SFJNP> temp;
    int size = pq.size();
    cout << "Gantt Chart-> ";
    while (!pq.empty())
    {

        while (!pq.empty() && (time >= pq.top()[1]))
        {
            temp.push(pq.top());
            pq.pop();
        }
        while (time <= pq.top()[1])
        {
            cout << "N ";
            time += 1;
        }

        auto top = temp.top();
        time = max(time, top[1]);
        cout << top[0] << " ";
        schedule.push_back({top[0], top[1], top[2], time, time + top[2]});
        waitingTime += (time - top[1]);
        time += top[2];
        temp.pop();
        while (!temp.empty())
        {
            pq.push(temp.top());
            temp.pop();
        }
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
        pq.push({pid, arr, burst});
    }
    SFJNPscheduling(pq);
    print();
}