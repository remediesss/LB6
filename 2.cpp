#include <iostream>
#include <cstdlib>
#include <ctime>

int** create_weighted_adjacency_matrix(size_t size)
{
    int** matrix = (int**)malloc(size * sizeof(int*));
    if (!matrix)
    {
        return nullptr;
    }

    for (size_t i = 0; i < size; ++i)
    {
        matrix[i] = (int*)malloc(size * sizeof(int));
        if (!matrix[i])
        {
            for (size_t j = 0; j < i; ++j)
            {
                free(matrix[j]);
            }
            free(matrix);
            return nullptr;
        }
    }

    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = i + 1; j < size; ++j)
        {
            matrix[i][j] = rand() % 5;
            matrix[j][i] = matrix[i][j];
        }
    }

    for (size_t i = 0; i < size; ++i)
    {
        matrix[i][i] = 0;
    }

    return matrix;
}

void print_matrix(int** matrix, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void free_matrix(int** matrix, size_t size)
{
    if (!matrix)
    {
        return;
    }
    else
    {
        for (size_t i = 0; i < size; ++i)
        {
            free(matrix[i]);
        }
        free(matrix);
    }
}

void select_random_verticles(size_t size, size_t* v1, size_t* v2)
{
    *v1 = rand() % size;
    *v2 = rand() % size;
    while (*v2 == *v1)
    {
        *v2 = rand() % size;
    }
}

int** contraction_of_a_graph_edge(int** matrix, size_t size)
{
    size_t v1, v2;
    select_random_verticles(size, &v1, &v2);

    for (size_t i = 0; i < size; ++i)
    {
        if (i != v1 && i != v2)
        {
            matrix[v1][i] += matrix[v2][i];
            matrix[i][v1] = matrix[v1][i];
        }
    }

    for (size_t i = 0; i < size; ++i)
    {
        matrix[v2][i] = 0;
        matrix[i][v2] = 0;
    }

    return matrix;
}

int** identification_of_vertices(int** matrix, size_t size) 
{
    int** new_matrix = (int**)malloc((size - 1) * sizeof(int*));
    if (!new_matrix) 
    {
        return nullptr;
    }

    for (size_t i = 0; i < size - 1; ++i) 
    {
        new_matrix[i] = (int*)malloc((size - 1) * sizeof(int));
        if (!new_matrix[i]) {
            for (size_t j = 0; j < i; ++j) 
            {
                free(new_matrix[j]);
            }
            free(new_matrix);
            return nullptr;
        }
    }

    size_t v1, v2;
    select_random_verticles(size, &v1, &v2);

    size_t new_i = 0;
    for (size_t i = 0; i < size; ++i) 
    {
        if (i == v2) 
        {
            continue;
        }
        size_t new_j = 0;
        for (size_t j = 0; j < size; ++j) 
        {
            if (j == v2) 
            {
                continue;
            }
            if (i == v1 || j == v1) 
            {
                new_matrix[new_i][new_j] = matrix[v1][j] + matrix[v2][j == v1 ? v2 : j];
                if (i == v1 && j == v1) 
                {
                    new_matrix[new_i][new_j] = 0;
                }
            }
            else 
            {
                new_matrix[new_i][new_j] = matrix[i][j];
            }

            ++new_j;
        }
        ++new_i;
    }

    return new_matrix;
}


int** graph_vertex_splits(int** matrix, size_t size)
{
    size_t new_size = 2 * size;

    int** new_matrix = (int**)malloc(new_size * sizeof(int*));
    if (!new_matrix) 
    {
        return nullptr;
    }

    for (size_t i = 0; i < new_size; i++) 
    {
        new_matrix[i] = (int*)malloc(new_size * sizeof(int));
        if (!new_matrix[i]) 
        {
            for (size_t j = 0; j < i; ++j) 
            {
                free(new_matrix[j]);
            }
            free(new_matrix);
            return nullptr;
        }

        for (size_t j = 0; j < new_size; j++) 
        {
            new_matrix[i][j] = 0;
        }
    }

    for (size_t i = 0; i < size; i++) 
    {
        for (size_t j = 0; j < size; j++) 
        {
            if (matrix[i][j] != 0) 
            {
                int weight = matrix[i][j] / 2;
                new_matrix[i][j + size] = weight;
                new_matrix[j + size][i] = weight;
            }
        }
        new_matrix[i][i + size] = 1;
        new_matrix[i + size][i] = 1;
    }

    return new_matrix;
}


void print_identification_of_vertices(int** matrix, size_t size) 
{
    int** new_matrix = identification_of_vertices(matrix, size);
    if (!new_matrix) 
    {
        return;
    }

    std::cout << "after identification_of_vertices\n";
    print_matrix(new_matrix, size - 1);
    free_matrix(new_matrix, size - 1);
    std::cout << "\n\n";
}

void print_contraction_of_a_graph_edge(int** matrix, size_t size) 
{
    int** new_matrix = contraction_of_a_graph_edge(matrix, size);
    if (!new_matrix) 
    {
        return;
    }

    std::cout << "after contraction_of_a_graph_edge\n";
    print_matrix(new_matrix, size);
    free_matrix(new_matrix, size);
    std::cout << "\n\n";
}

void print_graph_vertex_splits(int** matrix, size_t size) 
{
    int** new_matrix = graph_vertex_splits(matrix, size);
    if (!new_matrix) 
    {
        return;
    }

    std::cout << "after graph_vertex_splits\n";
    print_matrix(new_matrix, 2 * size);
    free_matrix(new_matrix, 2 * size);
    std::cout << "\n\n";
}


void start()
{

    srand(static_cast<unsigned int>(time(nullptr)));

    while (true)
    {
        std::cout << "Enter size matrix (type size_t) : ";
        size_t size;
        std::cin >> size;
        if (!size)
        {
            return;
        }
        int** matrix = create_weighted_adjacency_matrix(size);
        if (!matrix)
        {
            std::cerr << "Error allocate\n";
            return;
        }
        print_matrix(matrix, size);
        std::cout << std::endl;

        std::cout << "identification of vertices: 1\n";
        std::cout << "rib contractions: 2\n";
        std::cout << "graph vertex splits: 3\n";
        std::cout << "Enter operation (type int) OR -1 for finish: ";

        int choice;
        std::cin >> choice;

        std::cout << std::endl;

        if (choice == -1)
        {
            std::cout << "Finish\n";
            return;
        }

        else if (choice == 1)
        {
            print_identification_of_vertices(matrix, size);
        }

        else if (choice == 2)
        {
            print_contraction_of_a_graph_edge(matrix, size);
        }

        else if (choice == 3)
        {
            print_graph_vertex_splits(matrix, size);
        }

        else
        {
            std::cout << "Wrong opetrarino\n";
        }

    }
}

int main()
{
    start();

    return 0;
}
