#include <fstream>
#define INF 999999

using namespace std;

ifstream in = ifstream("input.txt");
ofstream out = ofstream("output.txt");

template <class T>
class Node
{
public:
    T key;

    Node(T k)
    {
        key = k;
    }
};

template <class T>
class Edge
{
public:
    T source, destination;
    int weight;

    Edge(T s, T d, int w)
    {
        source = s;
        destination = d;
        weight = w;
    }
};

template <class T>
class Graph
{
public:
    Node<T> **V;
    Edge<T> **E;
    int n, m;

    struct dist_table
    {
        T Q;
        int D;
        bool K;
    };

    Graph(Node<T> **nodes, Edge<T> **edges, int num_nodes, int num_edges)
    {
        V = nodes;
        E = edges;
        n = num_nodes;
        m = num_edges;
    }

    void sort(dist_table *t, int n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (t[i].Q < t[j].Q)
                {
                    T tmp1 = t[i].Q;
                    t[i].Q = t[j].Q;
                    t[j].Q = tmp1;

                    int tmp2 = t[i].D;
                    t[i].D = t[j].D;
                    t[j].D = tmp2;

                    T tmp3 = t[i].K;
                    t[i].K = t[j].K;
                    t[j].K = tmp3;
                }
            }
        }
    }

    int cheaper(dist_table *t, int n)
    {
        int v = INF;
        int index;

        for (int i = 0; i < n; i++)
        {
            if (t[i].K == false && t[i].D < v)
            {
                v = t[i].D;
                index = i;
            }
        }

        return index;
    }

    void Dijkstra(T s, T d)
    {

        dist_table *t = new dist_table[n];

        for (int i = 0; i < n; i++)
        {
            t[i].Q = V[i]->key;
            t[i].D = INF;
            t[i].K = false;
        }

        int c;
        sort(t, n);

        for (int i = 0; i < n; i++)
        {
            if (t[i].Q == s)
            {
                t[i].D = 0;
                c = i;
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (t[c].Q == E[j]->source)
                {
                    int h = -1;

                    for (int k = 0; k < n; k++)
                    {
                        if (E[j]->destination == t[k].Q)
                        {
                            h = k;
                            break;
                        }
                    }

                    if (t[h].D > t[c].D + E[j]->weight)
                        t[h].D = t[c].D + E[j]->weight;
                }
            }

            t[c].K = true;
            c = cheaper(t, n);
        }

        for (int i = 0; i < n; i++)
        {
            if (t[i].Q == d)
                out << t[i].D << endl;
        }
    }
};

template <class T>
class Task
{
public:
    Task(int n, int m)
    {
        Node<T> **V = new Node<T> *[n];
        for (int i = 0; i < n; i++)
        {
            T v;

            in >> v;

            V[i] = new Node<T>(v);
        }

        Edge<T> **E = new Edge<T> *[m];
        for (int i = 0; i < m; i++)
        {
            char c;
            T s, d;
            int w;

            in >> c >> s;
            // in >> c;
            in >> d;
            // in >> c;
            in >> w >> c;

            E[i] = new Edge<T>(s, d, w);
        }

        Graph<T> *G = new Graph<T>(V, E, n, m);

        T source, destination;
        in >> source >> destination;

        G->Dijkstra(source, destination);
    }
};

int main()
{
    for (int i = 0; i < 100; i++)
    {
        int n, m;
        string type;

        in >> n >> m >> type;

        if (type == "int")
            Task<int> *t = new Task<int>(n, m);
        if (type == "double")
            Task<double> *t = new Task<double>(n, m);
    }
    return 0;
}