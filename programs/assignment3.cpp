#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <string>

using namespace std;

/* ======================================================
   SMART CITY UTILITIES (GRAPH)
   ====================================================== */
struct Connection {
    int src, dest, cost;
};

int numCities = 5;
string cities[] = {"Pune", "Mumbai", "Nashik", "Jalgaon", "Nagar"};

vector<Connection> networkEdges = {
    {0, 1, 4}, {0, 2, 8}, {1, 2, 2}, {1, 3, 6}, {2, 3, 3}, {2, 4, 9}, {3, 4, 5}
};

// 1. DIJKSTRA: Fastest Data Routes
void findFastestDataRoutes() {
    vector<vector<pair<int, int>>> adj(numCities);
    for (auto &e : networkEdges) {
        adj[e.src].push_back({e.dest, e.cost});
        adj[e.dest].push_back({e.src, e.cost});
    }

    vector<int> dist(numCities, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[0] = 0;
    pq.push({0, 0});

    cout << "\n--- Optimized Data Routes (Starting from " << cities[0] << ") ---\n";
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto &x : adj[u]) {
            if (dist[x.first] > dist[u] + x.second) {
                dist[x.first] = dist[u] + x.second;
                pq.push({dist[x.first], x.first});
            }
        }
    }

    for (int i = 0; i < numCities; i++)
        cout << "To " << cities[i] << " : Latency " << dist[i] << "ms" << endl;
}

// 2. PRIM'S: Incremental Utility Expansion (Growing from the Hub)
void expandUtilityNetwork() {
    // Adjacency matrix
    vector<vector<int>> adj(numCities, vector<int>(numCities, 0));
    for (auto &e : networkEdges) {
        adj[e.src][e.dest] = e.cost;
        adj[e.dest][e.src] = e.cost;
    }

    vector<int> key(numCities, INT_MAX), parent(numCities, -1);
    vector<bool> inMST(numCities, false);

    key[0] = 0;

    cout << "\n--- Step-by-Step Utility Expansion (Prim's) ---\n";
    for (int count = 0; count < numCities - 1; count++) {
        int u = -1;
        for (int i = 0; i < numCities; i++)
            if (!inMST[i] && (u == -1 || key[i] < key[u]))
                u = i;

        inMST[u] = true;

        for (int v = 0; v < numCities; v++) {
            if (adj[u][v] && !inMST[v] && adj[u][v] < key[v]) {
                parent[v] = u;
                key[v] = adj[u][v];
            }
        }
    }

    for (int i = 1; i < numCities; i++) {
        cout << "Connect: " << cities[parent[i]] << " -> " << cities[i] 
             << " (Expansion Cost: ₹" << adj[i][parent[i]]*100 << "k)\n";
    }
}

// 3. KRUSKAL'S: Global Cost Minimization
struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n);
        for(int i=0; i<n; i++) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) parent[root_i] = root_j;
    }
};

void buildMinCostNetwork() {
    vector<Connection> edges = networkEdges;
    sort(edges.begin(), edges.end(), [](Connection a, Connection b) {
        return a.cost < b.cost;
    });

    DSU dsu(numCities);
    cout << "\n--- Global Infrastructure Map (Kruskal's) ---\n";
    for (auto &e : edges) {
        if (dsu.find(e.src) != dsu.find(e.dest)) {
            dsu.unite(e.src, e.dest);
            cout << "Bridge: " << cities[e.src] << " & " << cities[e.dest] << " (₹" << e.cost*100 << "k)\n";
        }
    }
}

/* ======================================================
   WAREHOUSE INVENTORY (ARRAY)
   ====================================================== */
struct Product {
    int id;
    string name;
    int priority; 
};

void sortWarehouseStock() {
    vector<Product> inventory = {
        {101, "Medical Kits", 12}, {202, "Water", 6},
        {303, "Flashlights", 25}, {404, "Batteries", 22}, {505, "Food", 2}
    };

    int n = inventory.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (inventory[j].priority < inventory[minIdx].priority)
                minIdx = j;
        swap(inventory[i], inventory[minIdx]);
    }

    cout << "\n--- Dispatch Priority List ---\n";
    for (auto &p : inventory)
        cout << "[" << p.priority << "] Item: " << p.name << " (ID: " << p.id << ")\n";
}

/* =======================
   MAIN INTERFACE
   ======================= */
int main() {
    int choice;
    do {
        cout << "\n===========================================\n";
        cout << "      CITY INFRASTRUCTURE MANAGER\n";
        cout << "===========================================\n";
        cout << "1. Dijkstra: Route Data Packets (Fastest)\n";
        cout << "2. Prim's: Expand Utilities (Step-by-Step)\n";
        cout << "3. Kruskal's: Total Infrastructure (Cheapest)\n";
        cout << "4. Selection: Sort Emergency Supplies\n";
        cout << "5. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: findFastestDataRoutes(); break;
            case 2: expandUtilityNetwork(); break;
            case 3: buildMinCostNetwork(); break;
            case 4: sortWarehouseStock(); break;
        }
    } while (choice != 5);
    return 0;
}