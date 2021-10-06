#include <iostream>
#include <queue>
#include <iomanip>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;
struct FCFS
{
    bool operator()(const vector<int> &a, const vector<int> &b)
    {
        return a[1] > b[1];
    }
};
vector<vector<int>> schedule;
void RoundRobin(priority_queue<vector<int>, vector<vector<int>>, FCFS> &pq, int robin)
{
    int time = 0;
    int waitingTime = 0;
    int size = pq.size();
    cout << "Gantt Chart-> ";
    queue<vector<int>> temp;
    while (!(pq.empty() && temp.empty()))
    {
        while (!pq.empty() && time >= pq.top()[1])
        {
            temp.push(pq.top());
            pq.pop();
        }
        if (temp.empty())
        {
            time += 1;
            cout << "N ";
            continue;
        }
        else
        {
            queue<vector<int>> a;
            while (!temp.empty())
            {
                auto t = temp.front();
                temp.pop();
                for (int i = 0; i < robin && t[2] > 0; i++)
                {
                    cout << t[0] << " ";
                    t[3] = min(time, t[3]);
                    t[2] -= 1;
                    time += 1;
                    if (t[2] == 0)
                    {
                        break;
                    }
                }
                if (t[2] == 0)
                {
                    t[4] = time;

                    schedule.push_back(t);
                    waitingTime += time - t[3];
                }
                else
                {
                    a.push(t);
                }
                while (!pq.empty() && time >= pq.top()[1])
                {
                    temp.push(pq.top());
                    pq.pop();
                }
            }
            temp = a;
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
    int robin;
    cout << "Time Quantum-> ";
    cin >> robin;
    for (int i = 0; i < totalProcesses; i++)
    {
        cout << "Enter process ID, Arrival Time, Burst time:- ";
        int pid, arr, burst;
        cin >> pid >> arr >> burst;
        pq.push({pid, arr, burst, INT32_MAX, INT32_MAX});
    }
    RoundRobin(pq, robin);
    print();
}