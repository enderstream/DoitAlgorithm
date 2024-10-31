#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int solution(int N, int M, vector<vector<int>> &matrix);
bool check_bound(int i, int j, int N, int M);

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int N, M;
    cin >> N >> M;
    vector<vector<int>> matrix(N, vector<int>(M, 0));
    for (int i = 0; i < N; i++)
    {
        string str;
        cin >> str;
        for (int j = 0; j < M; j++)
            matrix[i][j] = str[j] - '0';
    }

    cout << solution(N, M, matrix);
    return 0;
}

int solution(int N, int M, vector<vector<int>> &matrix)
{
    queue<vector<int>> Q;
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    vector<vector<int>> delta = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    Q.push({0, 0, 1});
    visited[0][0] = true;

    while (!Q.empty())
    {
        vector<int> next = Q.front();
        Q.pop();

        if (next[0] == N - 1 && next[1] == M - 1)
            return next[2];

        for (auto d : delta)
        {
            int ni = next[0] + d[0];
            int nj = next[1] + d[1];
            if (check_bound(ni, nj, N, M) && matrix[ni][nj] == 1 && !visited[ni][nj])
            {
                visited[ni][nj] = true;
                Q.push({ni, nj, next[2] + 1});
            }
        }
    }
    return -1;
}

bool check_bound(int i, int j, int N, int M)
{
    return 0 <= i && i < N && 0 <= j && j < M;
}