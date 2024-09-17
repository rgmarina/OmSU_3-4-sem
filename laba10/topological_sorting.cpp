#include <bits/stdc++.h>

using namespace std;

class Graph {
public:
    Graph(int vertices) : vertices(vertices), adjList(vertices) {}

    void addEdge(int u, int v) {//добавляем ребра в граф
        adjList[u].push_back(v);
    }

    bool isCyclicUtil(int start, vector<bool>& visited, vector<bool>& inStack) {
        if (!visited[start]) {
            visited[start] = true;
            inStack[start] = true;

            for (int neighbor : adjList[start]) {
                if (!visited[neighbor] && isCyclicUtil(neighbor, visited, inStack)) {
                    return true;
                } else if (inStack[neighbor]) {
                    return true;
                }
            }
        }
        inStack[start] = false;
        return false;
    }

    bool isCyclic() {
        vector<bool> visited(vertices, false);
        vector<bool> inStack(vertices, false);

        for (int i = 0; i < vertices; ++i) {
            if (!visited[i] && isCyclicUtil(i, visited, inStack)) {
                return true;
            }
        }
        return false;
    }

    void topologicalSortUtil(int start, vector<bool>& visited, vector<int>& component) {
        visited[start] = true;

        for (int neighbor: adjList[start]) {
            if (!visited[neighbor]) {
                topologicalSortUtil(neighbor, visited, component);
            }
        }

        component.push_back(start);
    }

    vector<int> topologicalSort() {
        vector<int> component;

        vector<bool> visited(vertices, false);

        for (int i = 0; i < vertices; ++i) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, component);
            }
        }

        return component;
    }

private:
    int vertices;
    vector<vector<int>> adjList; // двумерный массив для хранения путей, если то между вершинами пишет элемент с которым связан
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;

    Graph graph(n);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph.addEdge(a, b);
    }

    if (graph.isCyclic()) {
        cout << "В графе есть цикл" << endl;
        return 0;
    }

    vector<int> components = graph.topologicalSort();
    reverse(components.begin(), components.end());

    for (int i = 0; i < n; ++i) {
        cout << components[i] << " ";
    }
    cout << endl;


    return 0;
}
