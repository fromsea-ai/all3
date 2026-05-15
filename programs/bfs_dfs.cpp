#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void inputGraph(vector<vector<int>>& adj) {
    int v, e;
    cout << "Enter no. of vertices : ";
    cin >> v;

    adj.assign(v, vector<int>());

    cout << "Enter no. of edges : ";
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

void dfshelper(vector<vector<int>>& adj, vector<bool>& visited, int s, vector<int>& res,int target) {
    visited[s] = true;
    if(s==target){
        res.push_back(s);
        return;
    }
    res.push_back(s);

    for (int neighbor : adj[s]) {
        if (!visited[neighbor]) {
            dfshelper(adj, visited, neighbor, res,target);
        }
    }
}

vector<int> dfs(vector<vector<int>>& adj, int startNodeIndex = -1,int target) {
    int numVertices = adj.size();
    vector<bool> visited(numVertices, false);
    vector<int> res;
    
    if (startNodeIndex >= 0 && startNodeIndex < numVertices) {
        dfshelper(adj, visited, startNodeIndex, res,target);
    }

    for (int i = 0; i < numVertices; ++i) {
        if (!visited[i]) {
            dfshelper(adj, visited, i, res,target);
        }
    }
    return res;
}

vector<int> bfs(vector<vector<int>>& adj, int startNodeIndex = 0,int target) {
    int numVertices = adj.size();
    if (numVertices == 0) return {};

    vector<bool> visited(numVertices, false);
    vector<int> res;
    queue<int> q;

    q.push(startNodeIndex);
    visited[startNodeIndex] = true;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        if(curr==target){
            res.push_back(curr);
            return res;
        }
        res.push_back(curr);

        for (int neighbor : adj[curr]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return res;
}


void printTraversal(vector<int>& order) {
    for (int i : order) {
        cout<<i<<" ";
    }
    cout<<endl;
}

void menuDriven(vector<vector<int>>& adj){
    bool flag = true;
    while(flag){
        int ch;
        cout<<"\nMenu\n"
            <<"1. BFS Traversal\n"
            <<"2. DFS Traversal\n"
            <<"3. Exit\n"
            <<"\nEnter choice: ";
        
        cin>>ch;

        switch(ch){
            case 1:{
                int startNodeIndex;
                cout << "Enter start node index (0 to " << adj.size() - 1 << "): ";
                cin >> startNodeIndex;

                if (startNodeIndex < 0 || startNodeIndex >= adj.size()) {
                    cout << "Invalid start index entered. Defaulting to index 0" << endl;
                    startNodeIndex = 0;
                }

                vector<int> bfsOrder = bfs(adj, startNodeIndex);
                cout << "BFS traversal: ";
                printTraversal(bfsOrder);
                break;
            }

            case 2:{
                int startNodeIndex;
                cout << "Enter start node index (0 to " << adj.size() - 1 << "): ";
                cin >> startNodeIndex;

                if (startNodeIndex < 0 || startNodeIndex >= adj.size()) {
                    cout << "Invalid start index entered. Defaulting to index 0" << endl;
                    startNodeIndex = 0;
                }

                vector<int> dfsOrder = dfs(adj, startNodeIndex);
                cout << "DFS traversal: ";
                printTraversal(dfsOrder);
                break;
            }

            case 3:
                flag = false;
                break;

            default:cout<<"Invalid choice. Try Again !!!\n";
        }
    }
}

int main() {
    vector<vector<int>> adj;
    inputGraph(adj);

    menuDriven(adj);

    return 0;
}
