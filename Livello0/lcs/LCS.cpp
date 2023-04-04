#include <fstream>

using namespace std;

int lcs(string X, string Y, int n, int m)
{
    int L[n + 1][m + 1];

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (i == 0 || j == 0)
                L[i][j] = 0;

            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;

            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }

    return L[n][m];
};

int main()
{
    ifstream in = ifstream("input.txt");
    ofstream out = ofstream("output.txt");

    for (int i = 0; i < 100; i++)
    {
        int n, m;
        string a, b;
        in >> n >> m >> a >> b;

        out << lcs(a, b, n, m) << endl;
    }
    return 0;
}