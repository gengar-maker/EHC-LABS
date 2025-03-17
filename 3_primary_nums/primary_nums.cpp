#include <iostream>

int isprime( int x )
{
    for( int y = 2; y * y <= x; y++ )
    {
        if( x % y == 0 ) return 0;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    int num = 0;
    int def_num = 100000000;
    if (argc != 2)
    {
        std::cerr << "Usage: primary_nums.exe search-range [default is 100000000].\n";
        num = def_num;
    }
    else
    {
        num = atoi(argv[1]);
        if (num < 0)
        {
            std::cerr << "Search range must be positive. Use default value: 100000000.\n";
            num = def_num;
        }
    }
    int sum = 0;
    for( int i = 2; i <= num ; i++ )
    {
        sum += isprime ( i );
    }
    printf( "Number of primes numbers: %d", sum );
    
    return 0;
}