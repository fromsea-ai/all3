#include <bits/stdc++.h>
using namespace std;

// ================= GRAPH COLORING =================

void printSolution(vector<int>& color) {

    cout << "\nSolution Exists:\n";
    cout << "Assigned Colors:\n";

    for (int i = 0; i < color.size(); i++) {

        cout << "Vertex "
             << i
             << " ---> Color "
             << color[i]
             << endl;
    }
}

bool isSafe(int v,
            vector<vector<int>>& graph,
            vector<int>& color,
            int c) {

    for (int i = 0; i < graph.size(); i++) {

        // Adjacent vertex with same color
        if (graph[v][i] &&
            color[i] == c)

            return false;
    }

    return true;
}

bool graphColoringUtil(vector<vector<int>>& graph,
                       int m,
                       vector<int>& color,
                       int v) {

    // All vertices colored
    if (v == graph.size())
        return true;

    // Try all colors
    for (int c = 1; c <= m; c++) {

        if (isSafe(v,graph,color,c)) {
            color[v] = c;
            if (graphColoringUtil(graph,m,color,v + 1))
                return true;
            // Backtracking
            color[v] = 0;
        }
    }

    return false;
}

void graphColoring() {

    /*
        (3)---(2)
         |   / |
         |  /  |
         | /   |
        (0)---(1)
    */

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

    if (!graphColoringUtil(graph,
                           m,
                           color,
                           0)) {

        cout << "\nSolution does not exist.\n";
        return;
    }

    printSolution(color);
}

// ================= N QUEENS =================

bool isValid(int row,
             int col,
             int n,
             vector<vector<int>>& board) {

    // Check left row
    for (int j = 0; j < col; j++) {

        if (board[row][j])
            return false;
    }

    // Upper diagonal
    for (int i = row - 1,
             j = col - 1;

         i >= 0 && j >= 0;

         i--, j--) {

        if (board[i][j])
            return false;
    }

    // Lower diagonal
    for (int i = row + 1,
             j = col - 1;

         i < n && j >= 0;

         i++, j--) {

        if (board[i][j])
            return false;
    }

    return true;
}

bool solveQueens(int col,
                 int n,
                 vector<vector<int>>& board) {

    // All queens placed
    if (col == n)
        return true;

    for (int row = 0;
         row < n;
         row++) {

        if (isValid(row,
                    col,
                    n,
                    board)) {

            board[row][col] = 1;

            if (solveQueens(col + 1,
                            n,
                            board))

                return true;

            // Backtracking
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

    vector<vector<int>> board(
        n,
        vector<int>(n, 0)
    );

    bool found =
        solveQueens(0,
                    n,
                    board);

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

// ================= MAIN MENU =================

int main() {

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