#include <iostream>
#include <random>
#include <chrono>

using namespace std;

const int SIZE_AB = 10000000;
const int SIZE_C = 100;

#define TYPE double

TYPE __attribute__((aligned(32))) array_c[SIZE_C];

TYPE __attribute__((aligned(32))) array_a[SIZE_AB];
TYPE __attribute__((aligned(32))) array_b[SIZE_AB];

void setup(TYPE *table, int size);

// #pragma omp declare simd simdlen(4)
inline void my_serial_function(TYPE *arr_a, TYPE *arr_b, int ind)
{
    double ret = 0;
    int j = 0;
#pragma nounroll
    while (j < SIZE_C - 1 && ret < arr_a[ind] * 1000)
    {
        ret += array_c[j];
        j += 1;
    }
    arr_a[ind] = ret + arr_b[ind];
}

int main()
{
    setup(array_a, SIZE_AB);
    setup(array_b, SIZE_AB);
    setup(array_c, SIZE_C);

    auto start = chrono::high_resolution_clock::now();
    // #pragma omp simd
    for (int i = 0; i < SIZE_AB; ++i)
    {
        double tmp = 0.;
        int j = 0;
#pragma nounroll
        while (j < SIZE_C - 1 && tmp < array_a[i] * 1000)
        {
            tmp += array_c[j];
            j += 1;
        }
        array_a[i] = array_b[i] + tmp;
    }
    auto stop = chrono::high_resolution_clock::now();

    cout << "execution time simple " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << " mseconds\n";

    start = chrono::high_resolution_clock::now();
#pragma omp simd
    for (int i = 0; i < SIZE_AB; ++i)
    {
        my_serial_function(array_a, array_b, i);
    }
    stop = chrono::high_resolution_clock::now();

    cout << "execution time with vectorized function " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << " mseconds\n";
}

void setup(TYPE *table, int size)
{
    for (int w = 0; w < size; w++)
    {
        table[w] = rand() % 1000 / 3 + 1;
    }
}