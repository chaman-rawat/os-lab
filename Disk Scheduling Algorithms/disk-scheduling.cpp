#include <bits/stdc++.h>
using namespace std;
#define LEFT 0
#define RIGHT 199

class Solution {
   public:
    void fcfs(vector<int>& disks, int i_pos) {
        int n = disks.size();
        int total_seek = 0;

        for (int i = 0; i < n; ++i) {
            if (i == 0)
                total_seek += abs(disks[i] - i_pos);
            else
                total_seek += abs(disks[i] - disks[i - 1]);
        }

        cout << "Total number of seek operations : " << total_seek;
    }

    void scan(vector<int>& disks, int i_pos, bool to_left) {
        int total_seek = 0;
        if (to_left) {
            total_seek = i_pos;
            int maxVal = *max_element(disks.begin(), disks.end());
            total_seek += maxVal;
        } else {
            total_seek = RIGHT - i_pos;
            int minVal = *min_element(disks.begin(), disks.end());
            total_seek += RIGHT - minVal;
        }

        cout << "Total number of seek operations : " << total_seek;
    }

    void cscan(vector<int>& disks, int i_pos, bool to_left) {
        int total_seek;

        if (to_left) {
            total_seek = i_pos;
            total_seek += RIGHT;

            int minVal = RIGHT;
            for (int disk : disks) {
                if (disk > i_pos)
                    minVal = min(minVal, disk);
            }
            total_seek += RIGHT - minVal;
        } else {
            total_seek = RIGHT - i_pos;
            total_seek += RIGHT;

            int maxVal = 0;
            for (int disk : disks) {
                if (disk < i_pos)
                    maxVal = max(maxVal, disk);
            }

            total_seek += maxVal;
        }

        cout << "Total number of seek operations : " << total_seek;
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
#endif
    Solution sol;
    int n, i_pos;
    cin >> n >> i_pos;

    vector<int> arr(n);
    for (auto& a : arr)
        cin >> a;

    sol.fcfs(arr, i_pos);
    cout << endl;
    sol.scan(arr, i_pos, true);
    cout << endl;
    sol.cscan(arr, i_pos, false);
    return 0;
}