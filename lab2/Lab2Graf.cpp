#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>

class Graph {
private:
    std::unordered_map<int, std::vector<int>> adjList;

public:
    void addVertex(int vertex) {
        if (adjList.find(vertex) == adjList.end()) {
            adjList[vertex] = std::vector<int>();
        }
    }

    void addEdge(int vertex1, int vertex2) {
        adjList[vertex1].push_back(vertex2);
    }

    void bfsStepByStep(int startVertex) {
        std::unordered_set<int> visited;
        std::queue<int> queue;
        queue.push(startVertex);
        visited.insert(startVertex);

        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();

            // Вивід поточного вузла, черги та відвіданих вузлів
            std::cout << "Current node: " << current << std::endl;
            std::cout << "Turn: ";
            std::queue<int> tempQueue = queue;
            while (!tempQueue.empty()) {
                std::cout << tempQueue.front() << " ";
                tempQueue.pop();
            }
            std::cout << std::endl;
            std::cout << "Visited nodes: ";
            for (int vertex : visited) {
                std::cout << vertex << " ";
            }
            std::cout << std::endl;
            std::cout << "----" << std::endl;

            const std::vector<int>& neighbors = adjList[current];
            for (int neighbor : neighbors) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    queue.push(neighbor);
                }
            }
        }
    }
};

int main() {
    // Створюємо граф та додаємо вершини
    Graph graph;
    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);
    graph.addVertex(5);
    graph.addVertex(6);
    graph.addVertex(7);

    // Додаємо ребра відповідно до опису графа
    graph.addEdge(0, 1);
    graph.addEdge(0, 3);
    graph.addEdge(0, 4);
    graph.addEdge(1, 2);
    graph.addEdge(1, 5);
    graph.addEdge(2, 6);
    graph.addEdge(4, 7);

    // BFS покроково, починаючи з 0
    graph.bfsStepByStep(0);

    std::cout << "Search complete." << std::endl;

    return 0;
}
