#include <fstream>
#include <algorithm>

using namespace std;

ifstream in = ifstream("input.txt");
ofstream out = ofstream("output.txt");

int main()
{
    for (int i = 0; i < 100; i++)
    {
        int n, m;
        in >> n >> m;

        int o[n];

        for (int j = 0; j < n; j++)
            in >> o[j];

        sort(o, o + n, greater<int>());

        int tot = 0;

        for (int j = 0; j < m; j++)
            tot += o[j];

        out << tot << endl;
    }
    return 0;
}