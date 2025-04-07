#include <cstdlib>

class Graph {
private:
    int** m_adj_matr;
    int m_num_verts;
public:
    Graph(int num_verts) : m_num_verts(num_verts) {
        // m_adj_matr = new ;
    }

    Graph() = default;

    ~Graph() {}
};

int main()
{
    {
        Graph gr;
    }
    int g = 0;
    return 0;
}