#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <stdexcept>

std::vector<char> topologicalSortDemukron(std::vector<std::pair<char, char>>& edges) {
    std::unordered_map<char, std::vector<char>> adjList;
    std::unordered_map<char, int> inDegree;
    std::unordered_set<char> nodes;

    // Заповнення списку суміжності та підрахунок вхідних ступенів
    for (auto& edge : edges) {
        char u = edge.first;
        char v = edge.second;

        adjList[u].push_back(v);
        inDegree[v]++;
        nodes.insert(u);
        nodes.insert(v);
    }

    std::queue<char> zeroInDegreeQueue;
    for (char node : nodes) {
        if (inDegree[node] == 0) {
            zeroInDegreeQueue.push(node);
        }
    }

    std::vector<char> result;
    int level = 0;

    while (!zeroInDegreeQueue.empty()) {
        std::queue<char> newZeroInDegreeQueue;
        std::vector<char> currentLevel;

        while (!zeroInDegreeQueue.empty()) {
            char node = zeroInDegreeQueue.front();
            zeroInDegreeQueue.pop();
            currentLevel.push_back(node);

            for (char neighbor : adjList[node]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    newZeroInDegreeQueue.push(neighbor);
                }
            }
        }

        result.insert(result.end(), currentLevel.begin(), currentLevel.end());
        while (!newZeroInDegreeQueue.empty()) {
            zeroInDegreeQueue.push(newZeroInDegreeQueue.front());
            newZeroInDegreeQueue.pop();
        }
        level++;
    }

    if (result.size() != nodes.size()) {
        throw std::runtime_error("The graph contains cycles, topological sorting is impossible.");
    }

    return result;
}

int main() {
    std::vector<std::pair<char, char>> edges = {
        {'a', 'b'},
        {'a', 'd'},
        {'a', 'e'},
        {'b', 'c'},
        {'c', 'e'},
        {'c', 'f'},
        {'d', 'e'},
        {'e', 'f'}
    };

    std::vector<char> sortedNodes = topologicalSortDemukron(edges);

    std::cout << "Topological sorting: ";
    for (char node : sortedNodes) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    return 0;
}
