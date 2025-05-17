#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

vector<vector<int>> get_matrix(const string& file_name) {
    ifstream file(file_name);
    vector<vector<int>> matrix;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        int value;
        vector<int> row;
        while (ss >> value) {
            row.push_back(value);
        }
        matrix.push_back(row);
    }

    return matrix;
}

void print_matrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<int>> shimbell(const vector<vector<int>>& matrix, int steps, const string& mode) {
    int size = matrix.size();
    vector<vector<int>> result = matrix;

    for (int step = 0; step < steps - 1; ++step) {
        vector<vector<int>> new_result(size, vector<int>(size, 0));

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                vector<int> candidates;

                for (int k = 0; k < size; ++k) {
                    int a = result[i][k];
                    int b = matrix[k][j];
                    if (a != 0 && b != 0) {
                        candidates.push_back(a + b);
                    }
                }

                if (!candidates.empty()) {
                    if (mode == "min") {
                        new_result[i][j] = *min_element(candidates.begin(), candidates.end());
                    } else {
                        new_result[i][j] = *max_element(candidates.begin(), candidates.end());
                    }
                } else {
                    new_result[i][j] = 0;
                }
            }
        }
        result = new_result;
    }
    return result;
}

int main() {
    string file_name = "g41.txt";
    auto matrix = get_matrix(file_name);
    
    cout << "Введена матрица:" << endl;
    print_matrix(matrix);
    
    string mode;
    int mode_code;
    cout << "1. Кратчайший путь" << endl;
    cout << "2. Длиннейший путь" << endl;
    cin >> mode_code;
    if (mode_code == 1) {
        mode = "min";
    }
    else if (mode_code == 2) {
        mode = "max";
    }
    
    int steps;
    cout << "Введите количество переходов: ";
    cin >> steps;
    
    auto result = shimbell(matrix, steps, mode);
    
    cout << "\nРезультат:" << endl;
    print_matrix(result);

    return 0;
}
