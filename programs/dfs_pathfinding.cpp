#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <stack>

using namespace std;

void inputGraph(vector<vector<int>>& adj) {
    int v, e;
    cout << "Enter no. of vertices: ";
    cin >> v;

    adj.assign(v, vector<int>());

    cout << "Enter no. of edges: ";
    cin >> e;

    cout << "Enter edges (v1 v2 as indices 0 to " << v - 1 << "):" << endl;
    for (int i = 0; i < e; i++) {
        int v1, v2;
        cin >> v1 >> v2;

        if (v1 >= 0 && v1 < v && v2 >= 0 && v2 < v) {
            adj[v1].push_back(v2);
            adj[v2].push_back(v1);
        } else {
            cout << "Invalid vertex index entered." << endl;
            i--;
        }
    }
}

bool dfshelper(vector<vector<int>>& adj, vector<bool>& visited, int s, int target, unordered_map<int, int>& parent) {
    visited[s] = true;

    if (s == target) {
        return true;
    }

    for (int neighbor : adj[s]) {
        if (!visited[neighbor]) {
            parent[neighbor] = s;
            if (dfshelper(adj, visited, neighbor, target, parent)) {
                return true;
            }
        }
    }
    return false;
}

vector<int> dfs(vector<vector<int>>& adj, int startNodeIndex, int target) {
    int numVertices = adj.size();
    vector<bool> visited(numVertices, false);
    unordered_map<int, int> parent;
    vector<int> path;

    parent[startNodeIndex] = -1;

    if (dfshelper(adj, visited, startNodeIndex, target, parent)) {
        for (int v = target; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
    }

    return path;
}

vector<int> bfs(vector<vector<int>>& adj, int startNodeIndex, int target) {
    int numVertices = adj.size();
    vector<bool> visited(numVertices, false);
    unordered_map<int, int> parent;
    vector<int> path;
    queue<int> q;

    q.push(startNodeIndex);
    visited[startNodeIndex] = true;
    parent[startNodeIndex] = -1;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        if (curr == target) {
            for (int v = target; v != -1; v = parent[v]) {
                path.push_back(v);
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (int neighbor : adj[curr]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = curr;
                q.push(neighbor);
            }
        }
    }

    return {};
}

void printPath(const vector<int>& path) {
    if (path.empty()) {
        cout << "No path found!" << endl;
        return;
    }
    cout << "Path: ";
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;
}

void menuDriven(vector<vector<int>>& adj) {
    bool flag = true;
    while (flag) {
        int ch;
        cout << "\nMenu\n"
             << "1. BFS Path Finding\n"
             << "2. DFS Path Finding\n"
             << "3. Exit\n"
             << "\nEnter choice: ";

        cin >> ch;

        switch (ch) {
            case 1: {
                int startNodeIndex, target;
                cout << "Enter start node index (0 to " << adj.size() - 1 << "): ";
                cin >> startNodeIndex;
                cout << "Enter target node index (0 to " << adj.size() - 1 << "): ";
                cin >> target;

                if (startNodeIndex < 0 || startNodeIndex >= adj.size() || target < 0 || target >= adj.size()) {
                    cout << "Invalid start or target index entered." << endl;
                    break;
                }

                vector<int> bfsPath = bfs(adj, startNodeIndex, target);
                printPath(bfsPath);
                break;
            }

            case 2: {
                int startNodeIndex, target;
                cout << "Enter start node index (0 to " << adj.size() - 1 << "): ";
                cin >> startNodeIndex;
                cout << "Enter target node index (0 to " << adj.size() - 1 << "): ";
                cin >> target;

                if (startNodeIndex < 0 || startNodeIndex >= adj.size() || target < 0 || target >= adj.size()) {
                    cout << "Invalid start or target index entered." << endl;
                    break;
                }

                vector<int> dfsPath = dfs(adj, startNodeIndex, target);
                printPath(dfsPath);
                break;
            }

            case 3:
                flag = false;
                break;

            default:
                cout << "Invalid choice. Try Again !!!\n";
        }
    }
}

int main() {
    vector<vector<int>> adj;
    inputGraph(adj);

    menuDriven(adj);

    return 0;
}
