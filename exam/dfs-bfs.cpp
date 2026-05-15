#include <iostream>
#include <vector>
#include <queue>
using namespace std;


class SocialNetwork { 
    int people;
    vector<vector<int>> friendList;

    public:
    SocialNetwork(int n){
        people = n;
        friendList.resize(n);
    }

    bool isValid(int p){
        return (p >= 0 && p < people);
    }

    void addEdge(int p1, int p2){
        if(!isValid(p1) || !isValid(p2)){
            cout << "Invalid person IDs" << endl;
            return;
        }

        friendList[p1].push_back(p2);
        friendList[p2].push_back(p1);
        cout << "Edge between " << p1 << " and " << p2 << endl;
    }
    
    void dfs(int start, vector<bool> &visited){
        if(!isValid(start)){
            cout << "Invalid starting node" << endl;
            return;
        }

        visited[start] = 1;

        cout << start << " ";

        for(int f : friendList[start]){
            if(!visited[f]){
                dfs(f, visited);
            }
        }
    }

    void bfs(int start){
        if(!isValid(start)){
            cout << "Invalid starting node" << endl;
            return;
        }

        queue<int> q;
        vector<bool> visited(people, false);
        q.push(start);
        visited[start] = 1;

        while(!q.empty()){
            int node = q.front();
            q.pop();

            cout << node << " ";

            for(int f : friendList[node]){
                if(!visited[f]){
                    visited[f] = true;
                    q.push(f);
                }
            }
        }
    }

    void printGraph(){
        if(people == 0) cout << "Empty Graph" << endl;
        for(int i=0; i<people; i++){
            cout << "Person " << i << " -> ";
            for(int f : friendList[i]){
                cout << f << " "; 
            }
            cout << endl;
        }
    }
};
int main(){
    return 0;
}