#include <fstream>

using namespace std;

ifstream in = ifstream("input.txt");
ofstream out = ofstream("output.txt");

int min(int a, int b, int c)
{
    if (c < b)
    {
        if (c < a)
            return c;
        else
        {
            if (b < a)
                return b;
            else
                return a;
        }
    }
    else
    {
        if (b < a)
            return b;
        else
            return a;
    }
};

int p(char xi, char yj)
{
    if (xi == yj)
        return 0;
    else
        return 1;
};

int edit(string X, string Y, int n, int m)
{
    int L[n + 1][m + 1];

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (i == 0)
                L[i][j] = j;
            else if (j == 0)
                L[i][j] = i;
            else
                L[i][j] = min(L[i][j - 1] + 1, L[i - 1][j] + 1, L[i - 1][j - 1] + p(X[i - 1], Y[j - 1]));
        }
    }

    return L[n][m];
};

int main()
{
    for (int i = 0; i < 100; i++)
    {
        string a, b;
        int n, m;

        in >> n >> m >> a >> b;

        out << edit(a, b, n, m) << endl;
    }
    return 0;
}