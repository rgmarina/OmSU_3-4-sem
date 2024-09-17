#include <bits/stdc++.h>

using namespace std;

class Graph {
public:
    Graph(int vertices) : vertices(vertices), adjList(vertices + 1) {}

    void addEdge(int u, int v) {//добавляем пути между вершинами
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void dfs(int start, vector<bool>& visited, vector<int>& component) {//обход в глубину
        visited[start] = true;
        component.push_back(start);

        for (int neighbor : adjList[start]) {
            if (!visited[neighbor]) {
                dfs(neighbor, visited, component);
            }
        }
    }

    vector<vector<int>> findConnectedComponents() {
        vector<vector<int>> components;

        vector<bool> visited(vertices + 1, false);

        for (int i = 1; i < vertices; ++i) {//если не посещена, то это новый компонент
            if (!visited[i]) {
                vector<int> component;
                dfs(i, visited, component);
                components.push_back(component);
            }
        }

        return components;
    }

private:
    int vertices;
    vector<vector<int>> adjList; // двумерный массив для хранения путей, между вершинами пишет элемент с которым связан
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

    vector<vector<int>> components = graph.findConnectedComponents();

    for (vector<int> elem : components) {
        for (int element: elem) {
            cout << element << " ";
        }
        cout << endl;
    }

    return 0;
}
