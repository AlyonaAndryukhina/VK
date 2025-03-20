#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;

// Поиск в ширину
vector<int> BFS(const vector<vector<int>>& adjacencyList, int startVertex) 
{
    int numVertices = adjacencyList.size();
    vector<int> distances(numVertices, -1);
    queue<int> q;

    q.push(startVertex);
    distances[startVertex] = 0;

    while (!q.empty()) 
    {
        int current = q.front();
        q.pop();

        for (int neighbor : adjacencyList[current]) 
        {
            if (distances[neighbor] == -1) 
            {
                distances[neighbor] = distances[current] + 1;
                q.push(neighbor);
            }
        }
    }

    return distances;
}

int main() 
{
    // Открытие файла
    ifstream inputFile("graph.txt");
    if (!inputFile) 
    {
        cerr << "Error opening file!" << endl; // Обработка ошибки при открытии файла
        char c; cin >> c;
        return -1;
    }

    int numVertices, numEdges;
    inputFile >> numVertices >> numEdges;

    // Создание матрицы смежности
    vector<vector<int>> adjacencyList(numVertices);

    // Считываение значений ребер
    for (int i = 0; i < numEdges; ++i) {
        int u, v;
        inputFile >> u >> v;
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u); // Для ненаправленного графа
    }

    // Стратовая вершина
    int startVertex;
    inputFile >> startVertex;

    // Закрытие файла
    inputFile.close();

    // Вызов функции BFS и нахождение расстояний
    vector<int> distances = BFS(adjacencyList, startVertex);

    // Вывод результатов
    for (int i = 0; i < numVertices; i++) {
        cout << "Vertex " << i << ": " << distances[i] << endl;
    }

    char c; cin >> c;
    return 0;
}
