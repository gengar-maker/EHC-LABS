#include <cstdlib>
#include <iostream>
#include <vector>
#include <chrono>
#include <string>

#define MAX_DIST 30

class Graph {
private:
    uint64_t** m_adj_matr;
    size_t m_num_verts;
public:
    Graph(const Graph& other) : m_num_verts(other.m_num_verts)
    {
        m_adj_matr = new uint64_t*[m_num_verts];
        for (size_t i = 0; i < m_num_verts; ++i) {
            m_adj_matr[i] = new uint64_t[m_num_verts];
            for (size_t j = 0; j < m_num_verts; ++j) {
                m_adj_matr[i][j] = other.m_adj_matr[i][j];
            }
        }
    }
    Graph(size_t num_verts) : m_num_verts(num_verts)
    {
        m_adj_matr = new uint64_t*[m_num_verts];
        for (size_t i = 0; i < m_num_verts; ++i) {
            m_adj_matr[i] = new uint64_t[m_num_verts];
            for (size_t j = 0; j < m_num_verts; ++j) {
                m_adj_matr[i][j] = MAX_DIST;
            }
        }
    }

    Graph() = default;

    ~Graph()
    {
        for(size_t i = 0; i < m_num_verts; ++i) {
            delete[] m_adj_matr[i];
        }
        delete[] m_adj_matr;
    }

    void add_edge(size_t src, size_t dst, int dist)
    {
        if (src < 0 || src >= m_num_verts ||
            dst < 0 || dst >= m_num_verts ||
            dist < 0 || dist >= MAX_DIST) return;
        
        m_adj_matr[src][dst] = dist;
    }

    void print_adj_matr(void)
    {
        std::cout << std::endl;
        for (size_t i = 0; i < m_num_verts; ++i) {
            for (size_t j = 0; j < m_num_verts; ++j) {
                if ((m_adj_matr[i][j] < MAX_DIST))
                    std::cout << m_adj_matr[i][j] << ' ';
                else std::cout << '-' << ' ';
            }
            std::cout << std::endl;
        }
    }

    Graph get_shortest_paths(void)
    {
        Graph res_graph(*this);
        for (int iter = 0; iter < m_num_verts - 2; ++iter) {
            for(size_t i = 0; i < m_num_verts; ++i) {
                for(size_t j = 0; j < m_num_verts; ++j) {
                    for(size_t k = 0; k < m_num_verts; ++k) {
                        uint64_t tmp_dist = res_graph.m_adj_matr[i][k] + m_adj_matr[k][j];
                        if (res_graph.m_adj_matr[i][j] > tmp_dist) {
                            res_graph.m_adj_matr[i][j] = tmp_dist;
                        }
                    }
                }
            }
        }
        for(size_t i = 0; i < m_num_verts; ++i) { res_graph.m_adj_matr[i][i] = MAX_DIST; }
        return res_graph;
    }

    size_t get_graph_size() { return this->m_num_verts; }
};

void fill_rand_graph(Graph& graph) {
    size_t size = graph.get_graph_size();
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            if (i != j) {
                graph.add_edge(i, j, (rand() % (MAX_DIST + (MAX_DIST / 2))) + 1);
            }
        }
    }
}

int main(int argc, char** argv)
{
    size_t vertex = 0;
    if (argc != 2) {
        std::cerr << "Usage: graph.exe vertex_num [default is 400].\n";
        vertex = 400;
    } else {
        vertex = std::stoll(argv[1]);
    }

    srand(17);
    Graph gr1(5);
    fill_rand_graph(gr1);
    gr1.print_adj_matr();
    std::cout << "\nTest run started\n";
    Graph res_gr(gr1.get_shortest_paths());

    std::cout << "Test results:\n";
    
    res_gr.print_adj_matr();

    Graph gr_test(vertex);
    fill_rand_graph(gr_test);
    std::cout << "\nPerf run started\n";
    std::chrono::time_point t_start = std::chrono::high_resolution_clock::now();
    Graph res_test_gr(gr_test.get_shortest_paths());
    std::chrono::time_point t_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = t_end - t_start;
    std::cout << "Elapsed perf time: " << elapsed_time.count() << std::endl;

    return 0;
}
