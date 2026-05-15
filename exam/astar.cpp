#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> Pair;
const int N = 10;

vector<vector<int>> grid(N, vector<int>(N, 1));
bool hasSD = false;
Pair src, dest;

bool inRange(Pair p){
    return (p.first >=0 && p.first < N && p.second >=0 && p.second < N);
}

bool isUnblocked(Pair p){
    return grid[p.first][p.second] == 1;
}

double h(Pair a, Pair b){
    return abs(a.first - b.first) + abs(a.second - b.second);
}

void resetGrid(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            grid[i][j] = 1;
        }
    }
    hasSD = false;
    cout << "Grid Reset" << endl;
}

void addBlock(){
    cout << "Enter the x and y coordinates(0-9) of bloackage (-1 to exit): \n";
    int x, y; 

    while(true){
        cout << ">> ";
        cin >> x;
        if(x == -1) return;
        cin >> y;
        Pair p = {x, y};
        if(!inRange(p)){
            cout << "Invalid coordinates" << endl;
            continue;
        }
        if(hasSD && (p == src || p == dest)){
            cout << "Cannot block src and destination" << endl;
            continue;
        }
        grid[x][y] = 0;
    }
}

void showGrid(Pair src, Pair dest, bool hasSD, vector<Pair> path = {}){
    set<Pair> pathCells(path.begin(), path.end());

    cout << "S - Source" << endl;
    cout << "D - Destination" << endl;
    cout << "# - Blocked Cell" << endl;
    cout << "* - Path" << endl;
    cout << ". - Free Cell" << endl;

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            Pair cur = {i, j};
            if(hasSD && cur == src) cout << "S ";
            else if(hasSD && cur == dest) cout << "D ";
            else if (pathCells.count(cur)) cout << "* ";
            else if(grid[i][j] == 1) cout << ". ";
            else cout << "# ";
        }
        cout << endl;
    }
    cout << "================================" << endl;
}

struct Node{
    int x, y;
    double f, g;
};

struct Compare{
    bool operator()(Node const& a, Node const& b) const {
        return a.f > b.f;
    }
};

vector<Pair> aStarSearch(Pair start, Pair dest){
    priority_queue<Node, vector<Node>, Compare> open;
    map<Pair, double> gCost;
    map<Pair, Pair> parent;
    set<Pair> closed;

    open.push({start.first, start.second, h(start, dest), 0});
    gCost[start] = 0;

    vector<Pair> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while(!open.empty()){
        Node cur = open.top();
        open.pop();
        Pair current = {cur.x, cur.y};

        if(closed.count(current)) continue;
        closed.insert(current);

        if(current == dest){
            vector<Pair> path;

            while(current != start){
                path.push_back(current);
                current = parent[current];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        for(auto d : dir){
            Pair next = {current.first + d.first, current.second + d.second};
            if(!inRange(next) || !isUnblocked(next) || closed.count(next)) continue;
            double newG = gCost[current] + 1;
            if(!gCost.count(next) || newG < gCost[next]){
                gCost[next] = newG;
                parent[next] = current;
                double f = newG + h(next, dest);

                open.push({next.first, next.second, f, newG});
            }
        }
    }
    return {};
}

void printPath(const vector<Pair> &path){
    if(path.empty()){
        cout << "No path found" << endl;
        return;
    }

    cout << "\nPath:\n";

    for(auto p : path){
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;
    cout << "Path Cost: " << path.size() - 1 << endl;
}

int main(){
    int choice;
    do{
        cout << "1. Add Blocks\n";
        cout << "2. Add Source & Destination\n";
        cout << "3. Show Grid\n";
        cout << "4. Start A* Search\n";
        cout << "5. Reset Grid\n";
        cout << "6. Exit\n";
        cout << "----------------------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice){
            case 1:
                addBlock();
                break;
        
            case 2: {
                cout << "Enter src(x and y): ";
                cin >> src.first >> src.second;

                cout << "Enter destination (x y): ";
                cin >> dest.first >> dest.second;

                if(!inRange(src) || !isUnblocked(src) || !inRange(dest) || !isUnblocked(dest)){
                    cout << "Invalid Coordinates" << endl;
                    hasSD = false;
                }
                else {
                    hasSD = true;
                }
                break;
            }

            case 3:
                showGrid(src, dest, hasSD);
                break;

            case 4: {
                if(!hasSD){
                    cout << "Please set src and dest first" << endl;
                    break;
                }
                if(src == dest) {
                    cout << "Source and destination are same" << endl;
                    break;
                }
                vector<Pair> path = aStarSearch(src, dest);
                printPath(path);
                showGrid(src, dest, hasSD, path);
                break;
            }
            case 5:
                resetGrid();
                break;

            case 6:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice.\n";
            }
        } while(choice != 6);
    return 0;
}