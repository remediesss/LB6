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

int** union_matrix(int** matrix1, int** matrix2, size_t size)
{
    size_t new_size = size * 2;
    int** mergedMatrix = (int**)malloc(new_size * sizeof(int*));
    if (!mergedMatrix)
    {
        return nullptr;
    }

    for (size_t i = 0; i < new_size; ++i)
    {
        mergedMatrix[i] = (int*)malloc(new_size * sizeof(int));
        if (!mergedMatrix[i])
        {
            for (size_t j = 0; j < i; ++j)
            {
                free(mergedMatrix[j]);
            }
            free(mergedMatrix);
            return nullptr;
        }
    }
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
        {
            mergedMatrix[i][j] = matrix1[i][j];
        }
    }
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
        {
            mergedMatrix[size + i][size + j] = matrix2[i][j];
        }
    }

    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = size; j < new_size; ++j)
        {
            mergedMatrix[i][j] = 0;
            mergedMatrix[j][i] = 0;
        }
    }

    return mergedMatrix;
}


int** intersection_matrix(int** matrix1, int** matrix2, size_t size)
{
    int** intersected_matrix = (int**)malloc(size * sizeof(int*));
    if (!intersected_matrix)
    {
        return nullptr;
    }

    for (size_t i = 0; i < size; ++i)
    {
        intersected_matrix[i] = (int*)malloc(size * sizeof(int));
        if (!intersected_matrix[i])
        {
            for (size_t j = 0; j < i; ++j)
            {
                free(intersected_matrix[j]);
            }
            free(intersected_matrix);
            return nullptr;
        }

        for (size_t j = 0; j < size; ++j)
        {
            intersected_matrix[i][j] = matrix1[i][j] < matrix2[i][j] ? matrix1[i][j] : matrix2[i][j];
        }
    }

    return intersected_matrix;
}

int** ring_sum_matrix(int** matrix1, int** matrix2, size_t size)
{
    int** summed_matrix = (int**)malloc(size * sizeof(int*));
    if (!summed_matrix)
    {
        return nullptr;
    }

    for (size_t i = 0; i < size; ++i)
    {
        summed_matrix[i] = (int*)malloc(size * sizeof(int));
        if (!summed_matrix[i])
        {
            for (size_t j = 0; j < i; ++j)
            {
                free(summed_matrix[j]);
            }
            free(summed_matrix);
            return nullptr;
        }

        for (size_t j = 0; j < size; ++j)
        {
            size_t i_next = (i + 1) % size;
            size_t j_next = (j + 1) % size;

            summed_matrix[i][j] = matrix1[i][j] + matrix2[i_next][j_next];
        }
    }

    return summed_matrix;
}


void print_union_matrix(int** matrix1, int** matrix2, size_t size)
{
    int** matrix = union_matrix(matrix1,matrix2, size);
    std::cout << "after union_matrix\n";
    print_matrix(matrix, size);

    free_matrix(matrix1, size);
    free_matrix(matrix2, size);
    std::cout << "\n\n";

    free_matrix(matrix, size);
    return;
}

void print_intersection_matrix(int** matrix1, int** matrix2, size_t size)
{
    int** matrix = intersection_matrix(matrix1, matrix2, size);
    std::cout << "after intersection_matrix\n";
    print_matrix(matrix, size);

    free_matrix(matrix1, size);
    free_matrix(matrix2, size);

    std::cout << "\n\n";
    free_matrix(matrix, size);
    return;
}

void print_ring_sum_matrix(int** matrix1, int** matrix2, size_t size)
{
    int** matrix = ring_sum_matrix(matrix1, matrix2, size);
    std::cout << "after ring_sum_matrix\n";
    print_matrix(matrix, size);

    free_matrix(matrix1, size);
    free_matrix(matrix2, size);

    std::cout << "\n\n";
    free_matrix(matrix, size);
    return;
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
        int** matrix1 = create_weighted_adjacency_matrix(size);
        int** matrix2 = create_weighted_adjacency_matrix(size);
        if (!matrix1)
        {
            std::cerr << "Error allocate matrix1\n";
            return;
        }
        if (!matrix2)
        {
            std::cerr << "Error allocate matrix1\n";
            return;
        }
        print_matrix(matrix1, size);
        std::cout << std::endl;
        std::cout << std::endl;
        print_matrix(matrix2, size);


        std::cout << "union matrix: 1\n";
        std::cout << "intersection matrix: 2\n";
        std::cout << "ring sum: 3\n";
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
            print_union_matrix(matrix1, matrix2, size);
        }

        else if (choice == 2)
        {
            print_intersection_matrix(matrix1, matrix2, size);
        }

        else if (choice == 3)
        {
            print_ring_sum_matrix(matrix1, matrix2, size);
        }

        else
        {
            std::cout << "Wrong opetrarino\n";
        }

        std::cout << "\n\n";
    }
}

int main() 
{
    start();
    
    return 0;
}
