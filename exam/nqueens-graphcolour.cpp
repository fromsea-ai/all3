#include <bits/stdc++.h>
using namespace std;

void printsol(vector<int> & color){
    for (int i = 0; i < color.size(); i++) {
        cout << "Vertex " << i << " ---> Color " << color[i] << endl;
    }
}

bool isSafe(int v, int c, vector<vector<int>>& graph, vector<int>& color){
    for(int i=0; i<graph.size(); i++){
        if(graph[v][i] && color[i] == c) return false;
    }
    return true;
}

bool graphUtil(int v, int m, vector<vector<int>>& graph, vector<int>& color){
    if(v == graph.size()) return true;

    for(int c=1; c<=m; c++){
        if(isSafe(v, c, graph, color)){
            color[v] = c;
            if(graphUtil(v+1, m, graph, color)) return true;
            color[v] = 0;
        }
    }
    return false;
}

void graphColoring() {
    vector<vector<int>> graph = {

        {0,1,1,1},
        {1,0,1,0},
        {1,1,0,1},
        {1,0,1,0}
    };

    cout << "\nGraph Structure:\n";

    cout << "(3)---(2)\n";
    cout << " |   / |\n";
    cout << " |  /  |\n";
    cout << " | /   |\n";
    cout << "(0)---(1)\n";

    int m;

    cout << "\nEnter number of colors: ";
    cin >> m;

    int V = graph.size();

    vector<int> color(V, 0);

    if (!graphUtil(0, m, graph, color)) {
        cout << "\nSolution does not exist.\n";
        return;
    }

    printsol(color);
}

bool isValid(int row, int col, int n, vector<vector<int>>& board){
    for(int j=0; j<n; j++){
        if(board[row][j]) return false;
        for(int i=row-1,j=col-1; i>=0 && j >=0; i--,j--){
            if(board[i][j]) return false;
        }
        for(int i=row+1,j=col-1; i<n && j >=0; i++,j--){
            if(board[i][j]) return false;
        }
    }
    return true;
}

bool solveQueen(int col, int n, vector<vector<int>>& board){
    if(col == n) return true;
    for(int row=0; row<n; row++){
        if(isValid(row, col, n, board)){
            board[row][col] = 1;
            if(solveQueen(col+1, n, board)) return true;
            board[row][col] = 0;
        }
    }
    return false;
}

void nQueens() {

    int n;
    cout << "\nEnter value of N: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid size.\n";
        return;
    }

    vector<vector<int>> board(n,vector<int>(n, 0));

    bool found = solveQueen(0,n,board);
    if (!found) {
        cout << "\nNo solution exists.\n";
        return;
    }
    cout << "\nN-Queens Solution:\n\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j])
                cout << "Q ";
            else
                cout << ". ";
        }
        cout << endl;
    }
}

int main(){
    int choice;

    do {

        cout << "\n=====================================\n";
        cout << "      BACKTRACKING ALGORITHMS\n";
        cout << "=====================================\n";
        cout << "1. N-Queens Problem\n";
        cout << "2. Graph Coloring Problem\n";
        cout << "3. Exit\n";
        cout << "-------------------------------------\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {

        case 1:
            nQueens();
            break;

        case 2:
            graphColoring();
            break;

        case 3:
            cout << "Exiting Program...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 3);
    return 0;
}