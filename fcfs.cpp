// First Come First Serve
#include <bits/stdc++.h>
using namespace std;

class FCFS {
   public:
    vector<vector<int>> calculateFCFS(vector<int>& processes) {
        vector<vector<int>> result(processes.size(), vector<int>(3));

        for (int i = 0; i < processes.size(); ++i) {
            result[i][0] = result[i][2] = processes[i];
            if (i == 0) continue;
            result[i][1] = result[i - 1][2];
            result[i][2] += result[i - 1][2];
        }

        return result;
    }

    void showTable(vector<vector<int>> fcfs) {
        cout << "Processes  Burst-Time  Waiting-Time  Turn-around-Time" << endl;
        int i = 0;
        double avgWaitingTime = 0, avgTurnAroundTime = 0;
        for (auto& process : fcfs) {
            cout  << "\t" << ++i << "\t\t\t" << process[0] << "\t\t\t" << process[1] << "\t\t\t" << process[2] << endl;
            avgWaitingTime += process[1];
            avgTurnAroundTime += process[2];
        }

        avgWaitingTime /= fcfs.size();
        avgTurnAroundTime /= fcfs.size();

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

    FCFS solution;
    int n;
    cin >> n;
    vector<int> processes(n);
    for (auto& process : processes)
        cin >> process;

    auto fcfs = solution.calculateFCFS(processes);
    solution.showTable(fcfs);
    return 0;
}