#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

typedef unordered_map<int, vector<pair<int, int>>> pair_dict;

void solution();

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int V;
    cin >> V;
    pair_dict tree;
    for (int i = 1; i <= V; i++)
    {
        int v;
        cin >> v;
        while (true)
        {
            int u, d;
            cin >> u;
            if (u == -1)
                break;
            cin >> d;
            tree[i].push_back(pair<int, int>(u, d));
        }
    }

    solution();
    return 0;
}

void solution()
{
}