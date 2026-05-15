#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

// Disease Node
struct Disease {
    string name;
    vector<string> symptoms;
    int heuristic; // Used in A*
};

// Function to count symptom matches
int matchSymptoms(vector<string>& patient, vector<string>& diseaseSymptoms) {
    int count = 0;

    for (string s : patient) {
        if (find(diseaseSymptoms.begin(), diseaseSymptoms.end(), s) != diseaseSymptoms.end()) {
            count++;
        }
    }

    return count;
}

// BFS Search
void bfsSearch(vector<Disease>& diseases, vector<string>& patientSymptoms) {
    cout << "\n===== BFS Diagnosis =====\n";

    queue<Disease> q;

    for (auto d : diseases)
        q.push(d);

    while (!q.empty()) {
        Disease current = q.front();
        q.pop();

        int score = matchSymptoms(patientSymptoms, current.symptoms);

        cout << "Checking: " << current.name << endl;

        if (score >= 2) {
            cout << "Possible Disease Found: " << current.name << endl;
            return;
        }
    }

    cout << "No major disease detected.\n";
}

// DFS Search
void dfsSearch(vector<Disease>& diseases, vector<string>& patientSymptoms) {
    cout << "\n===== DFS Diagnosis =====\n";

    stack<Disease> st;

    for (auto d : diseases)
        st.push(d);

    while (!st.empty()) {
        Disease current = st.top();
        st.pop();

        int score = matchSymptoms(patientSymptoms, current.symptoms);

        cout << "Checking: " << current.name << endl;

        if (score >= 2) {
            cout << "Possible Disease Found: " << current.name << endl;
            return;
        }
    }

    cout << "No major disease detected.\n";
}

// Comparator for A*
struct compare {
    bool operator()(Disease a, Disease b) {
        return a.heuristic > b.heuristic;
    }
};

// A* Search
void aStarSearch(vector<Disease>& diseases, vector<string>& patientSymptoms) {
    cout << "\n===== A* Diagnosis =====\n";

    priority_queue<Disease, vector<Disease>, compare> pq;

    // Calculate heuristic dynamically
    for (auto d : diseases) {
        Disease temp = d;

        int matches = matchSymptoms(patientSymptoms, d.symptoms);

        // Smaller heuristic = better match
        temp.heuristic = d.symptoms.size() - matches;

        pq.push(temp);
    }

    while (!pq.empty()) {
        Disease current = pq.top();
        pq.pop();

        cout << "Checking: " << current.name << endl;

        int score = matchSymptoms(patientSymptoms, current.symptoms);

        if (score >= 2) {
            cout << "Most Probable Disease: " << current.name << endl;
            return;
        }
    }

    cout << "No major disease detected.\n";
}

int main() {

    vector<Disease> diseases = {

        {"Diabetes",
            {"thirst", "urination", "fatigue", "blurred_vision"},
            0},

        {"Hypertension",
            {"headache", "chest_pain", "fatigue"},
            0},

        {"Heart Disease",
            {"chest_pain", "fatigue", "high_bp"},
            0},

        {"Healthy",
            {"none"},
            0}
    };

    vector<string> patientSymptoms;

    int n;

    cout << "===== AI MEDICAL EXPERT SYSTEM =====\n";

    cout << "\nAvailable Symptoms:\n";
    cout << "- thirst\n";
    cout << "- urination\n";
    cout << "- fatigue\n";
    cout << "- blurred_vision\n";
    cout << "- headache\n";
    cout << "- chest_pain\n";
    cout << "- high_bp\n";

    cout << "\nHow many symptoms do you have? ";
    cin >> n;

    cout << "Enter symptoms one by one:\n";

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        patientSymptoms.push_back(s);
    }

    // Run Algorithms
    bfsSearch(diseases, patientSymptoms);

    dfsSearch(diseases, patientSymptoms);

    aStarSearch(diseases, patientSymptoms);

    return 0;
}