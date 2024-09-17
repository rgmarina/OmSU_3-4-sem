// Команда для компиляции: clang++ -std=c++20 -pedantic -pedantic-errors -Wall  -Wextra $(pkg-config --libs --cflags raylib) main.cpp -o main

#include <bits/stdc++.h>
#include <raylib.h>

using namespace std;

const int CANVAS_WIDTH = 1200;
const int CANVAS_HEIGHT = 800;

const float RADIUS_NODE = 0.8;
const float WIDTH_EDGE = 1.2;


struct Node {//узел
    long id;
    double lon;
    double lat;

    double x;
    double y;

    Node(long id, double lon, double lat) : id(id), lon(lon), lat(lat) {}

    bool operator==(const Node& other) const {
        return id == other.id && lon == other.lon && lat == other.lat;
    }
};

struct Edge {//ребро
    long u;
    long v;

    double ux;
    double uy;

    double vx;
    double vy;

    long dist; // расстояние между u-v

    Edge(long u, long v) : u(u), v(v) {}
};

double eucledean_dist(double x1, double y1, double x2, double y2) {//расстояние между двумя нодами
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

vector<Node> read_nodes(string path) {//чтение данных о вершинах
    fstream csv(path);

    // skip csv header
    string header;
    getline(csv, header);

    vector<Node> nodes;
    // read data
    for (string line; getline(csv, line);) {
        stringstream lineStream(line);
        string cell;

        getline(lineStream, cell, ',');
        long id = stol(cell);

        getline(lineStream, cell, ',');
        double lon = stod(cell);

        getline(lineStream, cell, ',');
        double lat = stod(cell);

        nodes.emplace_back(id, lon, lat);
    }

    return nodes;
}

vector<Edge> read_edges(string path) {
    fstream csv(path);

    // skip csv header
    string header;
    getline(csv, header);

    vector<Edge> edges;

    for (string line; getline(csv, line);) {
        stringstream lineStream(line);
        string cell;

        getline(lineStream, cell, ',');
        long u = stol(cell);

        getline(lineStream, cell, ',');
        long v = stol(cell);

        edges.emplace_back(u, v);
    }

    return edges;
}

struct GraphNode {
    long id;
    double distance;
    double heuristicEstimate; // Эвристическая оценка расстояния до целевой вершины
    bool visited;
    long previous; // Предыдущая вершина на пути к текущей

    GraphNode(long id) : id(id), distance(std::numeric_limits<double>::infinity()), heuristicEstimate(0),
                         visited(false), previous(-1) {}
};

double heuristic(const Node& first, Node& second) {
    return sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
}

stack<long> aStar(vector<Node>& nodes, vector<Edge>& edges, long startNodeId, long endNodeId) {
    unordered_map<long, size_t> node_id_to_pos;
    vector<GraphNode> graph;
    for (size_t i = 0; i < nodes.size(); ++i) {
        node_id_to_pos[nodes[i].id] = i;
        graph.emplace_back(nodes[i].id);
    }

    // Находим позицию стартовой и конечной вершины
    size_t startPos = node_id_to_pos[startNodeId];
    size_t endPos = node_id_to_pos[endNodeId];

    graph[startPos].distance = 0; // Начальная вершина имеет расстояние 0
    graph[startPos].heuristicEstimate = heuristic(nodes[startPos], nodes[endPos]);

    while (true) {
        // Находим вершину с наименьшим расстоянием среди непосещённых
        size_t minDistNodePos = 0;
        double minDist = std::numeric_limits<double>::infinity();
        for (size_t i = 0; i < graph.size(); ++i) {
            if (!graph[i].visited && (graph[i].distance + graph[i].heuristicEstimate) < minDist) {
                minDistNodePos = i;
                minDist = graph[i].distance + graph[i].heuristicEstimate;
            }
        }

        // Если все вершины посещены, выходим из цикла
        if (minDist == std::numeric_limits<double>::infinity()) {
            break;
        }

        auto& currentNode = graph[minDistNodePos];
        currentNode.visited = true;

        // Останавливаем алгоритм если достигнута конечная вершина
        if (currentNode.id == endNodeId) {
            break;
        }

        // Обновляем расстояние до смежных вершин
        for (auto& edge: edges) {
            if (edge.u == currentNode.id) {
                size_t vPos = node_id_to_pos[edge.v];
                auto& vNode = graph[vPos];
                double newDist = currentNode.distance + edge.dist;
                if (newDist < vNode.distance) {
                    vNode.distance = newDist;
                    vNode.previous = currentNode.id;
                    vNode.heuristicEstimate = heuristic(nodes[vPos], nodes[endPos]);
                }
            } else if (edge.v == currentNode.id) {
                size_t uPos = node_id_to_pos[edge.u];
                auto& uNode = graph[uPos];
                double newDist = currentNode.distance + edge.dist;
                if (newDist < uNode.distance) {
                    uNode.distance = newDist;
                    uNode.previous = currentNode.id;
                    uNode.heuristicEstimate = heuristic(nodes[uPos], nodes[endPos]);
                }
            }
        }
    }

    // Восстанавливаем путь от конечной вершины к начальной
    stack<long> path;
    long current = endNodeId;
    while (current != startNodeId) {
        path.push(current);
        current = graph[node_id_to_pos[current]].previous;
    }
    path.push(startNodeId);

    return path;
}

int main() {
    vector<Node> nodes = read_nodes("omsk_nodes.csv");
    vector<Edge> edges = read_edges("omsk_edges.csv");

    unordered_map<long, size_t> node_id_to_pos;
    for (size_t i = 0; i < nodes.size(); i++) {
        auto& node = nodes[i];
        node_id_to_pos[node.id] = i;
    }

    cout << nodes.size() << endl;
    cout << edges.size() << endl;

    double min_lon = nodes[0].lon;
    double max_lon = nodes[0].lon;
    double min_lat = nodes[0].lat;
    double max_lat = nodes[0].lat;

    for (auto& node: nodes) {
        if (min_lat > node.lat) {
            min_lat = node.lat;
        }
        if (min_lon > node.lon) {
            min_lon = node.lon;
        }
        if (max_lat < node.lat) {
            max_lat = node.lat;
        }
        if (max_lon < node.lon) {
            max_lon = node.lon;
        }
    }

    double delta_lon = max_lon - min_lon;
    double delta_lat = max_lat - min_lat;
    double scale = double(CANVAS_HEIGHT) / min(delta_lat, delta_lon);

    cout << delta_lon << " " << delta_lat << endl;

    cout << min_lon << " " << min_lat << "; " << max_lon << " " << max_lat
         << endl;

    for (auto& node: nodes) {
        node.x = (node.lon - min_lon) * scale;
        node.y = CANVAS_HEIGHT - (node.lat - min_lat) * scale;
    }

    for (auto& edge: edges) {//заполняем структуру данными и вычисляем расстояние
        auto& u = nodes[node_id_to_pos[edge.u]];
        auto& v = nodes[node_id_to_pos[edge.v]];
        edge.ux = u.x;
        edge.uy = u.y;
        edge.vx = v.x;
        edge.vy = v.y;

        edge.dist = eucledean_dist(edge.ux, edge.uy, edge.vx, edge.vy);
    }

    InitWindow(CANVAS_WIDTH, CANVAS_HEIGHT, "OMSK");
    SetTargetFPS(60);
    float scaleGraph = 1.0f;

    while (!WindowShouldClose()) {
        // Получаем текущие координаты мыши
        Vector2 mousePosition = GetMousePosition();

        if (IsKeyDown(KEY_UP)) {
            scaleGraph += 0.1f; // увеличиваем масштаб при нажатии стрелки вверх
            if (scaleGraph > 10.0f) {
                scaleGraph = 10.0f; // предотвращаем слишком большие значения масштаба
            }
        }
        if (IsKeyDown(KEY_DOWN)) {
            scaleGraph -= 0.1f; // уменьшаем масштаб при нажатии стрелки вниз
            if (scaleGraph < 0.1f) {
                scaleGraph = 0.1f; // предотвращаем отрицательные значения масштаба
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);//фон

        // Определяем смещение, используя текущие координаты мыши
        float offsetX = 0, offsetY = 0;
        static Vector2 previousMousePosition = {0, 0};
        static Node startNode = {LONG_MIN, 0, 0};
        static Node endNode = {LONG_MIN, 0, 0};
        static stack<long> path;

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            offsetX = mousePosition.x - previousMousePosition.x;
            offsetY = mousePosition.y - previousMousePosition.y;
        }
        previousMousePosition = mousePosition;

        static bool isMouseButtonPressed = false;

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !isMouseButtonPressed) {
            isMouseButtonPressed = true;

            for (auto& node: nodes) {
                // Проверяем, попадает ли мышь в окружность вершины
                if (CheckCollisionPointCircle(mousePosition, {static_cast<float>(node.x * scaleGraph),
                                                              static_cast<float>(node.y * scaleGraph)},
                                              RADIUS_NODE * scaleGraph)) {
                    // Если попали, выводим координаты вершины в консоль
                    if (startNode == Node(LONG_MIN, 0, 0)) {
                        startNode = node;
                    } else if (endNode == Node(LONG_MIN, 0, 0) && startNode != node) {
                        endNode = node;
                        path = aStar(nodes, edges, startNode.id, endNode.id);
                        stack<long> tmpPath = path;
                        while (!tmpPath.empty()) {
                            long nodeId = tmpPath.top();
                            tmpPath.pop();
                            cout << "-->" << nodeId;
                        }
                    } else if (startNode != Node(LONG_MIN, 0, 0) && endNode != Node(LONG_MIN, 0, 0) &&
                               startNode != node) {
                        startNode = node;
                        endNode = Node(LONG_MIN, 0, 0);
                        path = {};
                    } else {
                        cout << "Start: " << startNode.id << endl;
                        cout << "End: " << endNode.id << endl;
                        break;
                    }
                    cout << "Coordinates of clicked node: (" << node.x << ", " << node.y << ")" << endl;
                    break; // Прерываем цикл, так как вершины не могут пересекаться
                }
            }
        } else if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            isMouseButtonPressed = false;
        }

        // Обновляем координаты узлов с учётом смещения
        for (auto& node: nodes) {
            node.x += offsetX;
            node.y += offsetY;
        }

        // Обновляем координаты рёбер с учётом смещения
        for (auto& edge: edges) {
            edge.ux += offsetX;
            edge.uy += offsetY;
            edge.vx += offsetX;
            edge.vy += offsetY;
        }

        // Рисуем рёбра
        for (auto& edge: edges) {
            DrawLineEx({static_cast<float>(edge.ux * scaleGraph), static_cast<float>(edge.uy * scaleGraph)},
                       {static_cast<float>(edge.vx * scaleGraph), static_cast<float>(edge.vy * scaleGraph)},
                       WIDTH_EDGE * scaleGraph, BLACK);
        }
        stack<long> tmpPath = path;
        while (!tmpPath.empty()) {//пока путь не пустой, берем две вершины из стека
            long nodeIdFirst = tmpPath.top();
            tmpPath.pop();
            long nodeIdSecond = tmpPath.top();
            tmpPath.pop();
            for (auto& edge: edges) {
                if ((nodeIdFirst == edge.v && nodeIdSecond == edge.u) ||
                    (nodeIdFirst == edge.u && nodeIdSecond == edge.v)) {
                    if (!tmpPath.empty()) {
                        tmpPath.push(nodeIdSecond);
                    }
                    DrawLineEx({static_cast<float>(edge.ux * scaleGraph), static_cast<float>(edge.uy * scaleGraph)},
                               {static_cast<float>(edge.vx * scaleGraph), static_cast<float>(edge.vy * scaleGraph)},
                               WIDTH_EDGE * scaleGraph, PINK);
                    break;
                }
            }
        }

        // Рисуем узлы
        for (auto& node: nodes) {
            if (node == startNode) {
                DrawCircle(node.x * scaleGraph, node.y * scaleGraph, RADIUS_NODE * scaleGraph,
                           CLITERAL(Color){240, 43, 43, 255});
            } else if (node == endNode) {
                DrawCircle(node.x * scaleGraph, node.y * scaleGraph, RADIUS_NODE * scaleGraph,
                           CLITERAL(Color){166, 18, 18, 255});
            } else {
                DrawCircle(node.x * scaleGraph, node.y * scaleGraph, RADIUS_NODE * scaleGraph, SKYBLUE);
            }
        }

        EndDrawing();
    }


    CloseWindow();

    return 0;
}