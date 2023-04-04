#include <fstream>
#define INF 9999999

using namespace std;

ifstream in = ifstream("input.txt");
ofstream out = ofstream("output.txt");

int mcm(int n, int *a)
{
    int m[n + 1][n + 1];

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i >= j)
                m[i][j] = 0;
            else
                m[i][j] = INF;
        }
    }

    for (int d = 1; d < n; d++) // distanza tra gli indici
    {
        for (int i = 1; i < n; i++) // primo indice
        {
            int j = i + d; // secondo indice

            if (j < n + 1)
            {
                int q;

                for (int k = i; k < j; k++) // i <= k < j
                {
                    q = m[i][k] + m[k + 1][j] + a[i - 1] * a[k] * a[j];
                    if (q < m[i][j])
                        m[i][j] = q;
                }
            }
        }
    }

    return m[1][n];
};

int main()
{
    for (int i = 0; i < 100; i++)
    {
        int n;
        in >> n;

        int p[n + 1];

        for (int j = 0; j <= n; j++)
        {
            char c;

            if (j == 0)
            {
                int v1, v2;
                in >> c >> v1 >> c >> v2 >> c;
                p[j] = v1;
                j++;
                p[j] = v2;
            }
            else
            {
                int v;
                in >> c >> v >> c >> v >> c;
                p[j] = v;
            }
        }

        out << mcm(n, p) << endl;
    }
    return 0;
}