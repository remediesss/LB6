#include <iostream>
#include <cstdlib>
#include <ctime>

int** create_weighted_adjacency_matrix(size_t size) {
    int** matrix = (int**)malloc(size * sizeof(int*));
    if (!matrix) {
        return nullptr;
    }

    for (size_t i = 0; i < size; ++i) {
        matrix[i] = (int*)malloc(size * sizeof(int));
        if (!matrix[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(matrix[j]);
            }
            free(matrix);
            return nullptr;
        }
    }

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = i + 1; j < size; ++j) {
            matrix[i][j] = rand() % 10 + 1; // ñëó÷àéíûé âåñ îò 1 äî 10
            matrix[j][i] = matrix[i][j]; // ñèììåòðè÷íîñòü
        }
    }

    for (size_t i = 0; i < size; ++i) {
        matrix[i][i] = 0; // íåò ïåòåëü
    }

    return matrix;
}

void print_matrix(int** matrix, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void free_matrix(int** matrix, size_t size) {
    if (!matrix) {
        return;
    }
    for (size_t i = 0; i < size; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

void start() {
    srand(static_cast<unsigned int>(time(nullptr)));
    std::cout << "Enter size of the matrix (type size_t): ";
    size_t size;
    std::cin >> size;
    if (!size) {
        return;
    }

    int** m1 = create_weighted_adjacency_matrix(size);
    if (!m1) {
        std::cerr << "Error allocating memory for matrix 1\n";
        return;
    }
    std::cout << "Matrix M1:\n";
    print_matrix(m1, size);

    std::cout << std::endl;

    int** m2 = create_weighted_adjacency_matrix(size);
    if (!m2) {
        std::cerr << "Error allocating memory for matrix 2\n";
        return;
    }
    std::cout << "Matrix M2:\n";
    print_matrix(m2, size);

    free_matrix(m1, size);
    free_matrix(m2, size);
    std::cout << std::endl;
}

int main() {
    start();
}
