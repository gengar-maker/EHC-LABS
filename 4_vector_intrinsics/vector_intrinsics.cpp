#include <iostream>
#include <immintrin.h>
#include <malloc.h>

#include <chrono>

using namespace std;

// void check_vector_ext()
// {
//     cout << "SSE support:       " << __builtin_cpu_supports("sse") << endl;
//     cout << "SSE2 support:      " << __builtin_cpu_supports("sse2") << endl;
//     cout << "AVX support:       " << __builtin_cpu_supports("avx") << endl;
//     cout << "AVX2 support:      " << __builtin_cpu_supports("avx2") << endl;
//     cout << "AVX512 support:    " << __builtin_cpu_supports("avx512f") << endl;
// }

#define ARR_SIZE 512
#define ITERS 4000000

void simple_arr_mult(float res[], const float a[], const float b[], const size_t size)
{
    #pragma novector
    for (size_t iter = 0; iter < size; ++iter) {
        res[iter] = a[iter] + b[iter];
    }
}

void vector_arr_mult_u(float res[], const float a[], const float b[], const size_t size)
{
    #pragma nounroll
    for (size_t iter = 0; iter < size; iter += 8) {
        __m256 res_v;
        __m256 a_v = _mm256_loadu_ps(a + iter);
        __m256 b_v = _mm256_loadu_ps(b + iter);
        res_v = _mm256_add_ps(a_v, b_v);
        _mm256_storeu_ps(res + iter, res_v);
    }
}

int main() {
    cout << "Vector vs simple\n";
    // check_vector_ext();
    float** a = new float*[ITERS];
    float** b = new float*[ITERS];
    float res[ARR_SIZE];
    float res_v[ARR_SIZE];

    for (size_t i = 0; i < ITERS; ++i) {
        a[i] = (float*)_aligned_malloc(sizeof(float) * ARR_SIZE, 64);
        b[i] = (float*)_aligned_malloc(sizeof(float) * ARR_SIZE, 64);
        // a[i] = (float*)malloc(sizeof(float) * ARR_SIZE);
        // b[i] = (float*)malloc(sizeof(float) * ARR_SIZE);
        for (size_t j = 0; j < ARR_SIZE; ++j) {
            a[i][j] = b[i][j] = 1;
        }
    }

    chrono::time_point start = chrono::high_resolution_clock::now();
    #pragma novector
    for (size_t i = 0; i < ITERS; ++i) {
        simple_arr_mult(res, a[i], b[i], ARR_SIZE);
    }
    chrono::time_point end = chrono::high_resolution_clock::now();

    chrono::duration<double> time = end - start;
    cout << "Simple time: " << time.count() << endl;

    start = std::chrono::high_resolution_clock::now();
    #pragma novector
    for (int i = 0; i < ITERS; ++i) {
        vector_arr_mult_u(res_v, a[i], b[i], ARR_SIZE);
    }
    end = std::chrono::high_resolution_clock::now();

    time = end - start;
    cout << "Vectorized time: " << time.count() << endl;

    for (size_t i = 0; i < ARR_SIZE; ++i) {
        if (fabs(res[i] - res_v[i]) > 1e-6) {
            cout << "Incorrect answer on position: " << i << " : " << res[i] << " : " << res_v[i] << endl;
        }
    }

    for (size_t i = 0; i < ITERS; ++i) {
        _aligned_free(a[i]);
        _aligned_free(b[i]);
        // free(a[i]);
        // free(b[i]);
    }

    delete[] a;
    delete[] b;

    return 0;
}