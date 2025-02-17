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
            for (int k = 0; k < arrSize; k++)
            {
                product[i][j] += aMatrix[i][k] * bMatrix[k][j];
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

    for (int i = 0; i < num; i++)
    {
        aMatrix[i] = new float[num];
        bMatrix[i] = new float[num];
        product_simple[i] = new float[num];

        for (int j = 0; j < num; ++j)
        {
            product_simple[i][j] = 0;
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

    for (int i = 0; i < num; i++)
    {
        delete[] aMatrix[i];
        delete[] bMatrix[i];
        delete[] product_simple[i];
    }

    delete[] aMatrix;
    delete[] bMatrix;
    delete[] product_simple;
}

int main(int argc, char *argv[])
{
    mmult_task(argc, argv);
    return 0;
}
