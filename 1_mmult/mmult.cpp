#include <time.h>
#include <iostream>

#include <random>
#include <chrono>

using namespace std;

void init_matrix(double row, double col, double off, int arrSize, float **array)
{
    int i, j;
    for (i = 0; i < arrSize; i++)
    {
        for (j = 0; j < arrSize; j++)
        {
            array[i][j] = row * i + col * j + off;
        }
    }
}

void print_array(char *name, int arrSize, float **array)
{
    int i, j;

    cout << endl
         << name << endl;
    for (i = 0; i < arrSize; i++)
    {
        for (j = 0; j < arrSize; j++)
        {
            cout << "\t" << array[i][j];
        }
        cout << endl;
    }
}

template <typename val_t>
void multiply_simple(int arrSize, val_t **aMatrix, val_t **bMatrix, val_t **product)
{
    for (int i = 0; i < arrSize; i++)
    {
        for (int j = 0; j < arrSize; j++)
        {
            #pragma novector
            for (int k = 0; k < arrSize; k++)
            {
                product[i][j] += aMatrix[i][k] * bMatrix[k][j];
            }
        }
    }
}

template <typename val_t>
void multiply_sequential(int arrSize, val_t **aMatrix, val_t **bMatrix, val_t **product)
{
    for (int i = 0; i < arrSize; i++)
    {
        for (int k = 0; k < arrSize; k++)
        {
            #pragma novector
            for (int j = 0; j < arrSize; j++)
            {
                product[i][j] += aMatrix[i][k] * bMatrix[k][j];
            }
        }
    }
}

template <typename val_t>
void multiply_sequential_blocked(int arrSize, val_t **aMatrix, val_t **bMatrix, val_t **product)
{
    int block_size = 128;

    for (int ii = 0; ii < arrSize; ii += block_size)
    {
        int max_i = min(ii + block_size, arrSize);
        for (int jj = 0; jj < arrSize; jj += block_size)
        {
            int max_j = min(jj + block_size, arrSize);
            for (int kk = 0; kk < arrSize; kk += block_size)
            {
                int max_k = min(kk + block_size, arrSize);
                for (int i = ii; i < max_i; i++) {
                    for (int k = kk; k < max_k; k++) {
                        #pragma novector
                        for (int j = jj; j < max_j; j++)
                        {
                            product[i][j] += aMatrix[i][k] * bMatrix[k][j];
                        }
                    }
                }
            }
        }
    }
}

void mmult_task(int argc, char *argv[])
{
    int num = 0;
    if (argc != 2)
    {
        cerr << "Usage: mmult.exe arraySize [default is 1024].\n";
        num = 1024;
    }
    else
    {
        num = atoi(argv[1]);
        if (num < 0)
        {
            cerr << "Array dimensions must be positive; setting it to 1024. \n"
                 << endl;
            num = 1024;
        }
        if (num > 9000)
        {
            cerr << "Array dimensions must not be greater than 9000; setting it to 9000. \n"
                 << endl;
            num = 9000;
        }
    }

    float **aMatrix = new float *[num];
    float **bMatrix = new float *[num];
    float **product_simple = new float *[num];
    float **product_seq = new float *[num];
    float **product_blocked = new float *[num];

    for (int i = 0; i < num; i++)
    {
        aMatrix[i] = new float[num];
        bMatrix[i] = new float[num];
        product_simple[i] = new float[num];
        product_seq[i] = new float[num];
        product_blocked[i] = new float[num];

        for (int j = 0; j < num; ++j)
        {
            product_simple[i][j] = product_seq[i][j] = product_blocked[i][j] = 0;
        }
    }

    init_matrix(3, -2, 1, num, aMatrix);
    init_matrix(-2, 1, 3, num, bMatrix);

    cout << "Size: " << num << " X " << num << endl;
    auto start = chrono::high_resolution_clock::now();
    multiply_simple(num, aMatrix, bMatrix, product_simple);
    auto stop = chrono::high_resolution_clock::now();

    if (num <= 6)
    {
        print_array((char *)("aMatrix"), num, aMatrix);
        print_array((char *)("bMatrix"), num, bMatrix);
        print_array((char *)("product_simple"), num, product_simple);
    }

    cout << "Elapsed time mmult simple = " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << " mseconds" << endl;

    start = chrono::high_resolution_clock::now();
    multiply_sequential(num, aMatrix, bMatrix, product_seq);
    stop = chrono::high_resolution_clock::now();

    if (num <= 6)
    {
        print_array((char *)("aMatrix"), num, aMatrix);
        print_array((char *)("bMatrix"), num, bMatrix);
        print_array((char *)("product_seq"), num, product_seq);
    }

    cout << "Elapsed time mmult sequential access = " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << " mseconds" << endl;

    start = chrono::high_resolution_clock::now();
    multiply_sequential_blocked(num, aMatrix, bMatrix, product_blocked);
    stop = chrono::high_resolution_clock::now();

    if (num <= 6)
    {
        print_array((char *)("aMatrix"), num, aMatrix);
        print_array((char *)("bMatrix"), num, bMatrix);
        print_array((char *)("product_blocked"), num, product_blocked);
    }

    cout << "Elapsed time mmult blocked = " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << " mseconds" << endl;

    for (int i = 0; i < num; ++i)
    {
        for (int j = 0; j < num; ++j)
        {
            if (product_seq[i][j] != product_blocked[i][j] || product_blocked[i][j] != product_simple[i][j])
            {
                cout << "Error while computations!\n";
                break;
            }
        }
    }

    for (int i = 0; i < num; i++)
    {
        delete[] aMatrix[i];
        delete[] bMatrix[i];
        delete[] product_simple[i];
        delete[] product_seq[i];
        delete[] product_blocked[i];
    }

    delete[] aMatrix;
    delete[] bMatrix;
    delete[] product_simple;
    delete[] product_seq;
    delete[] product_blocked;
}

int main(int argc, char *argv[])
{
    mmult_task(argc, argv);
    return 0;
}
