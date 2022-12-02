// Priority
#include <bits/stdc++.h>
using namespace std;

class Priority {
   public:
    vector<vector<int>> calculatePriority(vector<vector<int>> processes) {
        sort(processes.begin(), processes.end(), [](auto& a, auto& b) { return a[1] < b[1]; });
        vector<vector<int>> res;

        priority_queue<pair<int, int>> pq;
        vector<bool> visited(processes.size());

        int jobs_complete = 0;
        int time = 0;

        while (jobs_complete != processes.size()) {
            // Add new processs to the queue
            for (int i = 0; i < processes.size(); ++i) {
                if (visited[i] || processes[i][1] > time) continue;

                pq.push({processes[i][3], i});
                visited[i] = true;
            }

            if (pq.size()) {
                time += processes[pq.top().second][2];

                // TAT = CT - AT
                int turn_around_time = time - processes[pq.top().second][1];
                // WT = TAT - BT
                int waiting_time = turn_around_time - processes[pq.top().second][2];

                res.push_back({processes[pq.top().second][0],
                               processes[pq.top().second][1],
                               processes[pq.top().second][2],
                               waiting_time,
                               turn_around_time});

                pq.pop();
                ++jobs_complete;
            } else {
                ++time;
            }
        }
        return res;
    }

    void showTable(vector<vector<int>> p) {
        sort(p.begin(), p.end(), [](auto& a, auto& b) { return a[0] < b[0]; });
        cout << "Processes Arival-Time Burst-Time  Waiting-Time  Turn-around-Time" << endl;
        double avgWaitingTime = 0, avgTurnAroundTime = 0;
        for (auto& process : p) {
            cout << "\t" << process[0] << "\t\t\t" << process[1] << "\t\t\t" << process[2] << "\t\t\t" << process[3] << "\t\t\t" << process[4] << endl;
            avgWaitingTime += process[3];
            avgTurnAroundTime += process[4];
        }

        avgWaitingTime /= p.size();
        avgTurnAroundTime /= p.size();

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

    Priority solution;
    int n, i = 0;
    cin >> n;

    vector<vector<int>> processes(n, vector<int>(4));
    for (auto& process : processes) {
        process[0] = ++i;
        // Arrival Time     Burst Time      Priority
        cin >> process[1] >> process[2] >> process[3];
    }

    auto p = solution.calculatePriority(processes);
    solution.showTable(p);
    return 0;
}