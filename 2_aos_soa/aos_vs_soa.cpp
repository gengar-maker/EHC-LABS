#include <time.h>
#include <iostream>

#include <random>
#include <chrono>

using namespace std;

#define STRING_SIZE 1000

struct Object
{
    char opts_a[STRING_SIZE];
    int opts_b[3];
    float opts_c[3];
};

void init_objects(int arrSize, Object *array)
{
    mt19937 gen;
    int i;
    for (i = 0; i < arrSize; i++)
    {
        strcpy(array[i].opts_a, "some name");
        array[i].opts_b[0] = gen() % 1000;
        array[i].opts_b[1] = gen() % 1000;
        array[i].opts_b[2] = gen() % 1000;
        array[i].opts_c[0] = static_cast<float>(gen() % 1000);
        array[i].opts_c[1] = static_cast<float>(gen() % 1000);
        array[i].opts_c[2] = static_cast<float>(gen() % 1000);
    }
}

void compare_objects(int arrSize, Object *array)
{
    float max_dist = -1.f;

    for (int i = 0; i < arrSize; i++)
    {
        for (int j = 0; j < arrSize; j++)
        {
            float d_0 = array[i].opts_c[0] - array[j].opts_c[0];
            float d_1 = array[i].opts_c[1] - array[j].opts_c[1];
            float d_2 = array[i].opts_c[2] - array[j].opts_c[2];

            max_dist = max(max_dist, sqrt(d_0 * d_0 + d_1 * d_1 + d_2 * d_2));
        }
    }

    cout << "Max dist = " << max_dist << endl;
}

void comp_task(int argc, char *argv[])
{
    int num = 0;

    if (argc != 2)
    {
        cerr << "Usage: aos_soa.exe objArraySize [default is 40000].\n";
        num = 40000;
    }
    else
    {
        num = atoi(argv[1]);
        if (num < 0)
        {
            cerr << "Array dimensions must be positive; setting it to 40000. \n"
                 << endl;
            num = 40000;
        }
    }

    Object *objs = new Object[num];

    init_objects(num, objs);

    cout << "Size: " << num << endl;
    auto start = chrono::high_resolution_clock::now();
    compare_objects(num, objs);
    auto stop = chrono::high_resolution_clock::now();

    cout << "Elapsed time aos = " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << " mseconds" << endl;

    delete[] objs;
}

int main(int argc, char *argv[])
{
    comp_task(argc, argv);
    return 0;
}
