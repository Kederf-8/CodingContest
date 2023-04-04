#include <fstream>
#define INF 999999

using namespace std;

ifstream in = ifstream("input.txt");
ofstream out = ofstream("output.txt");

struct Edge
{
    int s, d, w;
};

void bellmanFord(int *V, Edge *E, int n, int m, int k, int s, int d)
{
    int D[n];

    for (int i = 0; i < n; i++)
        D[i] = INF;

    D[s] = 0;

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int u = E[j].s;
            int v = E[j].d;

            if (D[v] > D[u] + E[j].w)
                D[v] = D[u] + E[j].w;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (V[i] == d)
        {
            if (D[i] == INF)
                out << "inf." << endl;
            else
                out << D[i] << endl;
        }
    }
}

int main()
{
    for (int i = 0; i < 100; i++)
    {
        int n, m, k;
        in >> n >> m >> k;

        int V[n];

        for (int j = 0; j < n; j++)
            V[j] = j;

        Edge E[m];
        for (int j = 0; j < m; j++)
        {
            char c;
            int s, d, w;

            in >> c >> s;
            // in >> c;
            in >> d;
            // in >> c;
            in >> w >> c;

            E[j].s = s;
            E[j].d = d;
            E[j].w = w;
        }

        int s, d;
        in >> s >> d;

        bellmanFord(V, E, n, m, k, s, d);
    }
    return 0;
}