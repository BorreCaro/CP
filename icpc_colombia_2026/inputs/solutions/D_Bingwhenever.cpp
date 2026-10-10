#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, b;
    while (cin >> n >> k >> b && (n != 0 || k != 0 || b != 0)) {
        vector<string> name(n);
        vector<vector<int>> card(n, vector<int>(k));
        for (int i = 0; i < n; i++) {
            cin >> name[i];
            for (int& x : card[i]) cin >> x;
        }
        unordered_map<int, int> when;          // número -> paso en que sale
        when.reserve(2 * b);
        for (int s = 1; s <= b; s++) {
            int x;
            cin >> x;
            when[x] = s;
        }
        vector<int> finish(n, 0);
        int best = numeric_limits<int>::max();
        for (int i = 0; i < n; i++) {
            for (int x : card[i]) finish[i] = max(finish[i], when[x]);
            best = min(best, finish[i]);
        }
        vector<string> winners;
        for (int i = 0; i < n; i++)
            if (finish[i] == best) winners.push_back(name[i]);
        sort(winners.begin(), winners.end());
        for (size_t i = 0; i < winners.size(); i++)
            cout << winners[i] << (i + 1 == winners.size() ? '\n' : ' ');
    }
}
