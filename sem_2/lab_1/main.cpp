#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>


std::vector<std::vector<int>> get_matrix(std::string file_name) {
    std::ifstream file(file_name);

    std::vector<std::vector<int>> matrix;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<int> row;
        std::stringstream ss(line);
        int num;

        while (ss >> num) {
            row.push_back(num);
        }

        matrix.push_back(row);
    }
    file.close();
    
    return matrix;
}


std::vector<std::vector<int>> get_unweighted(std::vector<std::vector<int>> matrix) {
    for (auto& row : matrix) {
        for (auto& num : row) {
            if (num > 1) {
                num = 1;
            }
        }
    }

    return matrix;
}


void print_matrix(std::vector<std::vector<int>>& matrix) {
    std::cout << "  ";
    for (int col = 0; col < matrix[0].size(); col++) {
        std::cout << char('a' + col) << " ";
    }
    std::cout << "\n";

    for (int row = 0; row < matrix.size(); row++) {
        std::cout << char('a' + row) << " ";
        for (int num : matrix[row]) {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }
}


void dfs(const std::vector<std::vector<int>>& graph, int v, std::unordered_set<int>& visited, int start_v, std::vector<std::vector<int>>& reachability_matrix) {
    visited.insert(v);
    reachability_matrix[start_v][v] = 1;

    for (int i = 0; i < graph[v].size(); i++) {
        if (graph[v][i] == 1 && visited.find(i) == visited.end()) {
            dfs(graph, i, visited, start_v, reachability_matrix);
        }
    }
}


std::vector<std::unordered_set<int>> get_connectivity_components(std::vector<std::vector<int>> reachability_matrix) {
    std::vector<std::unordered_set<int>> connectivity_components;
    int size = reachability_matrix.size();
    for (int x = 0; x < size; x++) {
        std::unordered_set<int> connected_vertices;
        for (int y = 0; y < size; y++) {
            if (reachability_matrix[x][y] == 1) {                
                for (int j = 0; j < size; ++j) {
                    if (reachability_matrix[x][j] == 1) {
                        connected_vertices.insert(j);
                    }
                }

                for (int i = 0; i < reachability_matrix.size(); ++i) {
                    if (reachability_matrix[i][y] == 1) {
                        connected_vertices.insert(i);
                    }
                }
            }
        }
        if (std::find(connectivity_components.begin(), connectivity_components.end(), connected_vertices) == connectivity_components.end()) {
            connectivity_components.push_back(connected_vertices);    
        }
    }
    return connectivity_components;
}


void print_set(std::vector<std::unordered_set<int>>& connectivity_components) {
    for (const auto& inner : connectivity_components) {
        std::cout << "{ ";
        for (const auto& num : inner) {
            std::cout << static_cast<char>('a' + num) << " ";
        }
        std::cout << "}" << std::endl;
    }
}


int main() {
    std::string file_name = "g12.txt";
    std::vector<std::vector<int>> matrix = get_matrix(file_name);
    std::vector<std::vector<int>> unweighted_graph = get_unweighted(matrix);
    
    std::cout << "Введена матрица:\n";
    print_matrix(matrix);
    
    std::vector<std::vector<int>> reachability_matrix(matrix.size(), std::vector<int>(matrix.size(), 0));
    std::cout << "\nМатрица достижимости:\n";
    
    for (int i = 0; i < matrix.size(); i++) {
        std::unordered_set<int> visited;
        dfs(unweighted_graph, i, visited, i, reachability_matrix);
    }

    print_matrix(reachability_matrix);
    
    std::vector<std::unordered_set<int>> connectivity_components = get_connectivity_components(reachability_matrix);
    std::cout << "\nКомпоненты связности:\n";
    print_set(connectivity_components);

    return 0;
}
