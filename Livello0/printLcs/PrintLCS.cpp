#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

ifstream in = ifstream("input.txt");
ofstream out = ofstream("output.txt");

string lcs(string X, string Y, int n, int m)
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

    int i = n, j = m;
    int M = L[i][j];
    string C = "";

    while (M > 0)
    {
        int topLeft = L[i - 1][j - 1];
        int left = L[i][j - 1];
        int top = L[i - 1][j];

        if (M == left)
        {
            // out << "Sinistra" << endl;
            j--;
        }
        else if (M > left && M > topLeft)
        {
            if (M == top && X[i - 1] != Y[j - 1])
            {
                // out << "Salgo" << endl;
                i--;
            }
            else
            {
                // out << "Diagonale" << endl;
                M--;
                i--;
                j--;
                C += X[i];
            }
        }
    }

    reverse(C.begin(), C.end());

    return C;
};

int main()
{
    for (int i = 0; i < 100; i++)
    {
        string a, b;
        int n, m;

        in >> n >> m >> a >> b;

        out << lcs(a, b, n, m) << endl;
    }
    return 0;
}