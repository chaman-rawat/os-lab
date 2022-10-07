// Round Robin
#include <bits/stdc++.h>
using namespace std;

class Round_Robin {
   public:
    vector<vector<int>> calculateRR(vector<vector<int>> processes, int time_quantum) {
        sort(processes.begin(), processes.end(), [](auto& a, auto& b) { return a[2] < b[2]; });

        vector<vector<int>> res;
        int jobs_arrived = 0;
        int jobs_complete = 0;
        int time = processes[0][2];
        queue<int> readyQueue;
        readyQueue.push(0);

        while (jobs_complete != processes.size()) {
            int current_job = readyQueue.front();
            bool current_job_done = true;

            if (processes[current_job][3] > time_quantum) {
                // Running process not completed yet
                processes[current_job][3] -= time_quantum;
                time += time_quantum;
                current_job_done = false;
            } else {
                // Running process completed yet
                time += processes[current_job][3];
                processes[current_job][3] = 0;

                int turn_around_time = time - processes[current_job][2];
                int waiting_time = turn_around_time - processes[current_job][1];

                res.push_back(processes[current_job]);
                res.back().back() = waiting_time;
                res.back().push_back(turn_around_time);
            }

            // New processes arriving to Ready Queue
            for (int i = jobs_arrived + 1; i < processes.size(); ++i) {
                if (time >= processes[i][2]) {
                    readyQueue.push(i);
                    ++jobs_arrived;
                } else {
                    break;
                }
            }

            readyQueue.pop();
            if (current_job_done) {
                ++jobs_complete;
            } else {
                readyQueue.push(current_job);
            }
        }

        return res;
    }

    void showTable(vector<vector<int>> rr) {
        sort(rr.begin(), rr.end(), [](auto& a, auto& b) { return a[0] < b[0]; });
        cout << "Processes Burst-Time Arival-Time  Waiting-Time  Turn-around-Time" << endl;
        double avgWaitingTime = 0, avgTurnAroundTime = 0;
        for (auto& process : rr) {
            cout << "\t" << process[0] << "\t\t\t" << process[1] << "\t\t\t" << process[2] << "\t\t\t" << process[3] << "\t\t\t" << process[4] << endl;
            avgWaitingTime += process[3];
            avgTurnAroundTime += process[4];
        }

        avgWaitingTime /= rr.size();
        avgTurnAroundTime /= rr.size();

        cout << endl;
        cout << "Average waiting time = " << avgWaitingTime << endl;
        cout << "Average turn around time = " << avgTurnAroundTime << endl;
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    Round_Robin solution;
    int n, time_quantum, i = 0;
    cin >> n >> time_quantum;

    vector<vector<int>> processes(n, vector<int>(4));
    for (auto& process : processes) {
        process[0] = ++i;
        // Burst Time     Arrival Time
        cin >> process[1] >> process[2];
        // Remaining Burst Time
        process[3] = process[1];
    }

    auto rr = solution.calculateRR(processes, time_quantum);
    solution.showTable(rr);
    return 0;
}