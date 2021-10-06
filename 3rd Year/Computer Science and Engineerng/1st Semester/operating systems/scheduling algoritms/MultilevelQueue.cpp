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
        if (a[1] == b[1])
        {
            if (a[3] != b[3])
            {
                return a[3] == 0;
            }
            else
            {
                return a[0] > b[1];
            }
        }
        return a[1] > b[1];
    }
};

vector<vector<int>> schedule;
void multilevelScheduling(priority_queue<vector<int>, vector<vector<int>>, FCFS> &pq, int robin)
{
    int time = 0;
    int waitingTime = 0;
    int size = pq.size();
    queue<vector<int>> temp;
    priority_queue<vector<int>, vector<vector<int>>, FCFS> background;
    cout << "Gantt Chart-> ";
    while (!(temp.empty() && pq.empty() && background.empty()))
    {
        while (!pq.empty() && time >= pq.top()[1])
        {
            auto t = pq.top();
            pq.pop();

            if (t[3] == 1)
            {
                temp.push(t);
            }
            else
            {
                background.push(t);
            }
        }
        if (!temp.empty() || !background.empty())
        {
            if (!temp.empty())
                while (!temp.empty())
                {
                    queue<vector<int>> a;
                    while (!temp.empty())
                    {
                        auto t = temp.front();
                        temp.pop();
                        for (int i = 0; i < robin && t[2] > 0; i++)
                        {
                            cout << t[0] << " ";
                            t[4] = min(time, t[4]);
                            t[2] -= 1;
                            time += 1;
                            if (t[2] == 0)
                            {
                                break;
                            }
                        }
                        if (t[2] == 0)
                        {
                            t[5] = time;

                            schedule.push_back(t);
                            waitingTime += time - t[4];
                        }
                        else
                        {
                            a.push(t);
                        }
                        while (!pq.empty() && time >= pq.top()[1])
                        {
                            auto t = pq.top();
                            pq.pop();
                            if (t[3] == 1)
                            {
                                temp.push(t);
                            }
                            else
                                background.push(t);
                        }
                    }
                    temp = a;
                }
            if (!background.empty())
            {
                auto t = background.top();
                background.pop();
                t[4] = min(time, t[4]);
                t[2] -= 1;
                cout << t[0] << " ";
                time += 1;
                if (t[2] == 0)
                {
                    t[5] = time;
                    schedule.push_back(t);
                }
                else
                {
                    background.push(t);
                }
            }
        }
        else
        {
            cout << "N ";
            time += 1;
        }
    }
    cout << "\nAverage Waiting time-> " << (float)(((float)waitingTime) / size) << "\n";
    cout << "Total Completion time->" << time << "\n";
}
void print()
{
    cout << "Process ID\tArrival Time\tBurst Time\tSystem Process\tStart Time\tCompletion Time\tTurn Around time\tWaiting Time\n";
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
    int robin;
    cout << "Time Quantum-> ";
    cin >> robin;
    for (int i = 0; i < totalProcesses; i++)
    {
        cout << "Enter process ID, Arrival Time, Burst time, System task:- ";
        int pid, arr, burst, sys;
        cin >> pid >> arr >> burst >> sys;
        pq.push({pid, arr, burst, sys, INT32_MAX, INT32_MAX});
    }
    multilevelScheduling(pq, robin);
    print();
}