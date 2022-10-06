// Shortest Job First
#include <bits/stdc++.h>
using namespace std;

class SJF {
   public:
    vector<vector<int>> calculateSJF(vector<vector<int>> processes) {
        vector<vector<int>> res;
        int jobs_remaining = processes.size();
        int time = 0;

        while (jobs_remaining--) {
            int current_job = -1;

            for (int i = 0; i < processes.size(); ++i) {
                if (processes[i][1] > time) continue;
                if (current_job == -1) current_job = i;
                if (processes[i][2] < processes[current_job][2])
                    current_job = i;
            }

            if (current_job == -1) {
                ++jobs_remaining;
                ++time;
                continue;
            }

            int waiting_time = time - processes[current_job][1];

            time += processes[current_job][2];

            int turn_around_time = time - processes[current_job][1];

            res.push_back(processes[current_job]);
            res.back().push_back(waiting_time);
            res.back().push_back(turn_around_time);
            processes[current_job][1] = INT_MAX;
        }

        return res;
    }

    void showTable(vector<vector<int>>& sjf) {
        double avgWaitingTime = 0, avgTurnAroundTime = 0;

        cout << "Processes Arival-Time Burst-Time  Waiting-Time  Turn-around-Time" << endl;
        for (auto& i : sjf) {
            cout << "\t" << i[0] << "\t\t\t" << i[1] << "\t\t\t" << i[2] << "\t\t\t" << i[3] << "\t\t\t" << i[4] << endl;
            avgWaitingTime += i[3];
            avgTurnAroundTime += i[4];
        }

        avgWaitingTime /= sjf.size();
        avgTurnAroundTime /= sjf.size();

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

    SJF solution;
    int n, i = 0;
    cin >> n;
    vector<vector<int>> processes(n, vector<int>(3));
    for (auto& process : processes) {
        process[0] = ++i;
        // Arrival Time     Burst Time
        cin >> process[1] >> process[2];
    }

    auto sjf = solution.calculateSJF(processes);
    solution.showTable(sjf);
    return 0;
}