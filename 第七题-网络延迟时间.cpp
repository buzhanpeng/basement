class Solution {
public:
    vector<int> dijkstra(int start, vector<vector<int>> &adj) {
        int n = adj.size();
        vector<bool> visited(n, false);
        vector<int> dis(n, INT_MAX);

        dis[start] = 0;
        auto cmp = [&](const auto &a, const auto &b) {
            return a.first > b.first;
        };

        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> smallQue(cmp);
        smallQue.push({dis[start], start});
        while (!smallQue.empty()) {

            auto [d, cur] = smallQue.top();
            smallQue.pop();

            visited[cur] = true;

            for (int next = 0; next < n; next++) {
                if (adj[cur][next] == INT_MAX) continue;
                if (dis[cur] + adj[cur][next] < dis[next]) {
                    dis[next] = dis[cur] + adj[cur][next];
                    smallQue.push({dis[next], next});
                }
            }
        }

        return dis;
    }

    int networkDelayTime(vector<vector<int>> &times, int n, int k) {

        vector<vector<int>> adj(n + 1, vector<int>(n + 1, INT_MAX));
        for (int i = 1; i < n + 1; i++) {
            adj[i][i] = 0;
        }

        for (auto &t : times) {
            adj[t[0]][t[1]] = t[2];
        }

        vector<int> dis = dijkstra(k, adj);

        int ans = 0;
        for (int i = 1; i < n + 1; i++) {
            ans = max(ans, dis[i]);
        }
        return ans == INT_MAX ? -1 : ans;
    }
};
