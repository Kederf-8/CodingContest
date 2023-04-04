#include <fstream>
#define INF 9999999

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

    Graph(Node<T> **v, Edge<T> **e)
    {
        V = v;
        E = e;
    }

    void bellmanFord(T s, T d, int n, int m)
    {
        int D[n];

        for (int i = 0; i < n; i++)
            D[i] = INF;

        for (int k = 0; k < n; k++)
        {
            if (V[k]->key == s)
                D[k] = 0;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                T ut = E[j]->source;
                T vt = E[j]->destination;
                int w = E[j]->weight;

                int u, v;

                for (int k = 0; k < n; k++)
                {
                    if (V[k]->key == ut)
                        u = k;
                    if (V[k]->key == vt)
                        v = k;
                }

                if (D[v] > D[u] + w)
                    D[v] = D[u] + w;
            }
        }

        for (int j = 0; j < m; j++)
        {
            T ut = E[j]->source;
            T vt = E[j]->destination;
            int w = E[j]->weight;

            int u, v;

            for (int k = 0; k < n; k++)
            {
                if (V[k]->key == ut)
                    u = k;
                if (V[k]->key == vt)
                    v = k;
            }

            if (D[u] != INF && D[u] + w < D[v])
            {
                out << "undef." << endl;
                return;
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (V[i]->key == d)
            {
                if (D[i] == INF)
                    out << "inf." << endl;
                else
                    out << D[i] << endl;
            }
        }
    }
};

template <class T>
class Task
{
public:
    Task(int v, int e)
    {
        Graph<T> *G;
        Node<T> **V = new Node<T> *[v];
        Edge<T> **E = new Edge<T> *[e];

        for (int i = 0; i < v; i++)
        {
            T k;
            in >> k;

            V[i] = new Node<T>(k);
        }

        for (int i = 0; i < e; i++)
        {
            char c;
            T s, d;
            int w;
            in >> c >> s;
            //in >> c;
            in >> d;
            //in >> c;
            in >> w >> c;

            E[i] = new Edge<T>(s, d, w);
        }

        G = new Graph<T>(V, E);

        T s, d;
        in >> s >> d;

        G->bellmanFord(s, d, v, e);
    }
};

int main()
{
    for (int i = 0; i < 100; i++)
    {
        int v, e;
        string type;

        in >> v >> e >> type;

        if (type == "int")
            Task<int> *t = new Task<int>(v, e);
        if (type == "double")
            Task<double> *t = new Task<double>(v, e);
    }
    return 0;
}