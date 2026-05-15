/*
Eventual Safe Nodes

There is a directed graph of n nodes with each node labeled from 0 to n - 1.
A node is a terminal node if there are no outgoing edges.
A node is a safe node if every possible path starting from that node leads to a terminal node (or another safe node).
Return an array containing all the safe nodes of the graph.
The answer should be sorted in ascending order.


Test case 1:

Enter Nodes: 7
Node 0: 1 2 -1
Node 1: 2 3 -1
Node 2: 5 -1
Node 3: 0 -1
Node 4: 5 -1
Node 5: -1
Node 6: -1

Safe Nodes: [ 2, 4, 5, 6 ]


Test Case 2:

Enter Nodes: 5
Node 0: 1 2 3 4 -1
Node 1: 1 2 -1
Node 2: 3 4 -1
Node 3: 0 4 -1
Node 4: -1

Safe Nodes: [ 4 ]
*/

// #include <iostream>
// #include <vector>
// #include <queue>
// #include <algorithm>
// #include <sstream>

// using namespace std;

// class Solution {
// public:
//     // 1: DFS (Cycle Detection)
//     bool dfsCheck(int node, vector<vector<int>>& graph, vector<int>& state) {
//         // state[i] = 0 (Unvisited), 1 (Visiting), 2 (Safe)
//         if (state[node] == 1) return false; // Cycle detected
//         if (state[node] == 2) return true;  // Already marked safe

//         state[node] = 1; // Mark as Visiting

//         for (int neighbor : graph[node]) {
//             if (!dfsCheck(neighbor, graph, state)) {
//                 return false; // If any path leads to unsafe/cycle, this node is unsafe
//             }
//         }

//         state[node] = 2; // Mark as Safe
//         return true;
//     }

//     vector<int> eventualSafeNodesDFS(vector<vector<int>>& graph) {
//         int n = graph.size();
//         vector<int> state(n, 0);
//         vector<int> safeNodes;

//         for (int i = 0; i < n; i++) {
//             if (dfsCheck(i, graph, state)) {
//                 safeNodes.push_back(i);
//             }
//         }
//         return safeNodes;
//     }

//     // 2: BFS (Topological Sort / Kahn's)
//     vector<int> eventualSafeNodesBFS(vector<vector<int>>& graph) {
//         int n = graph.size();
//         vector<vector<int>> revGraph(n);
//         vector<int> outDegree(n, 0);

//         // Build reverse graph and count out-degrees
//         for (int i = 0; i < n; i++) {
//             for (int node : graph[i]) {
//                 revGraph[node].push_back(i);
//             }
//             outDegree[i] = graph[i].size();
//         }

//         queue<int> q;
//         // Push terminal nodes (out-degree 0)
//         for (int i = 0; i < n; i++) {
//             if (outDegree[i] == 0) {
//                 q.push(i);
//             }
//         }

//         vector<int> safeNodes;
//         while (!q.empty()) {
//             int node = q.front();
//             q.pop();
//             safeNodes.push_back(node);

//             for (int prevNode : revGraph[node]) {
//                 outDegree[prevNode]--;
//                 if (outDegree[prevNode] == 0) {
//                     q.push(prevNode);
//                 }
//             }
//         }

//         sort(safeNodes.begin(), safeNodes.end());
//         return safeNodes;
//     }
// };

// void printVector(const vector<int>& v) {
//     if (v.empty()) {
//         cout << "[] (No safe nodes found)" << endl;
//         return;
//     }
//     cout << "[ ";
//     for (int i = 0; i < v.size(); i++) {
//         cout << v[i] << (i < v.size() - 1 ? ", " : " ");
//     }
//     cout << "]" << endl;
// }

// vector<vector<int>> getGraphInput() {
//     int n;
//     cout << "\n>> Enter number of nodes: ";
//     cin >> n;

//     vector<vector<int>> graph(n);
//     cout << ">> Enter neighbors for each node (enter -1 to stop for current node):" << endl;
    
//     for (int i = 0; i < n; i++) {
//         cout << "   Node " << i << " -> ";
//         int neighbor;
//         while (cin >> neighbor && neighbor != -1) {
//             if(neighbor >= 0 && neighbor < n) {
//                 graph[i].push_back(neighbor);
//             } else {
//                 cout << "   (Invalid node ignored. Range: 0 to " << n-1 << ")" << endl;
//             }
//         }
//     }
//     return graph;
// }

// int main() {
//     Solution sol;
//     vector<vector<int>> graph;
//     bool graphLoaded = false;
//     int choice;

//     do {
//         cout << "\n========================================" << endl;
//         cout << "   FIND EVENTUAL SAFE NODES (MENU)" << endl;
//         cout << "========================================" << endl;
//         cout << "1. Create New Graph" << endl;
//         cout << "2. Solve using DFS (Cycle Detection)" << endl;
//         cout << "3. Solve using BFS (Topological Sort)" << endl;
//         cout << "4. Show Current Graph" << endl;
//         cout << "5. Exit" << endl;
//         cout << "----------------------------------------" << endl;
//         cout << "Enter choice: ";
//         cin >> choice;

//         switch (choice) {
//             case 1:
//                 graph = getGraphInput();
//                 graphLoaded = true;
//                 cout << ">> Graph created successfully!" << endl;
//                 break;

//             case 2:
//                 if (!graphLoaded) {
//                     cout << ">> Error: Please create a graph first (Option 1)." << endl;
//                 } else {
//                     cout << "\n>> Calculating Safe Nodes using DFS..." << endl;
//                     vector<int> result = sol.eventualSafeNodesDFS(graph);
//                     cout << ">> Safe Nodes: ";
//                     printVector(result);
//                 }
//                 break;

//             case 3:
//                 if (!graphLoaded) {
//                     cout << ">> Error: Please create a graph first (Option 1)." << endl;
//                 } else {
//                     cout << "\n>> Calculating Safe Nodes using BFS..." << endl;
//                     vector<int> result = sol.eventualSafeNodesBFS(graph);
//                     cout << ">> Safe Nodes: ";
//                     printVector(result);
//                 }
//                 break;

//             case 4:
//                 if (!graphLoaded) {
//                      cout << ">> Graph is empty." << endl;
//                 } else {
//                     cout << "\n>> Adjacency List:" << endl;
//                     for(int i=0; i<graph.size(); i++) {
//                         cout << "   " << i << ": ";
//                         printVector(graph[i]);
//                     }
//                 }
//                 break;

//             case 5:
//                 cout << "Exiting program." << endl;
//                 break;

//             default:
//                 cout << "Invalid choice! Please try again." << endl;
//         }

//     } while (choice != 5);

//     return 0;
// }

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class SocialNetwork {
private:
    int people;
    vector<vector<int>> friendList;

public:
    SocialNetwork(int n) {
        people = n;
        friendList.resize(n);
    }

    // Validate person id
    bool isValidPerson(int p) {
        return (p >= 0 && p < people);
    }

    void addEdges(int p1, int p2) {

        if (!isValidPerson(p1) || !isValidPerson(p2)) {
            cout << "Invalid person ID!" << endl;
            return;
        }

        friendList[p1].push_back(p2);
        friendList[p2].push_back(p1);

        cout << "Edge between "
             << p1 << " and " << p2 << endl;
    }

    void dfs(int person, vector<bool>& visited) {

        if (!isValidPerson(person)) {
            cout << "Invalid starting node!" << endl;
            return;
        }

        visited[person] = true;

        cout << person << " ";

        for (int f : friendList[person]) {
            if (!visited[f]) {
                dfs(f, visited);
            }
        }
    }

    void bfs(int start) {

        if (!isValidPerson(start)) {
            cout << "Invalid starting node!" << endl;
            return;
        }

        queue<int> q;
        vector<bool> visited(people, false);

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {

            int node = q.front();
            q.pop();

            cout << node << " ";

            for (int f : friendList[node]) {

                if (!visited[f]) {
                    visited[f] = true;
                    q.push(f);
                }
            }
        }
    }

    void printGraph() {

        if (people == 0) {
            cout << "Graph is empty!" << endl;
            return;
        }

        cout << "\nSocial Network Graph:\n";

        for (int i = 0; i < people; i++) {

            cout << "Person " << i << " -> ";

            for (int f : friendList[i]) {
                cout << f << " ";
            }

            cout << endl;
        }
    }
};

int main() {

    int n;

    do {
        cout << "Enter number of people in network: ";
        cin >> n;

        if (n <= 0) {
            cout << "Number of people must be greater than 0!\n";
        }

    } while (n <= 0);

    SocialNetwork sn(n);

    int choice;

    do {

        cout << "\n================================";
        cout << "\n      SOCIAL NETWORK MENU";
        cout << "\n================================";
        cout << "\n1. Add Friendship";
        cout << "\n2. Print Graph";
        cout << "\n3. DFS Traversal";
        cout << "\n4. BFS Traversal";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";

        cin >> choice;

        switch (choice) {

        case 1: {

            int p1, p2;

            cout << "Enter two people IDs: ";
            cin >> p1 >> p2;

            sn.addEdges(p1, p2);

            break;
        }

        case 2: {

            sn.printGraph();

            break;
        }

        case 3: {

            int start;

            cout << "Enter starting point for DFS: ";
            cin >> start;

            vector<bool> vis(n, false);

            cout << "DFS Traversal: ";

            sn.dfs(start, vis);

            cout << endl;

            break;
        }

        case 4: {

            int start;

            cout << "Enter starting point for BFS: ";
            cin >> start;

            cout << "BFS Traversal: ";

            sn.bfs(start);

            cout << endl;

            break;
        }

        case 5:

            cout << "Exiting Program..." << endl;

            break;

        default:

            cout << "Invalid choice! Please enter 1-5." << endl;
        }

    } while (choice != 5);

    return 0;
}