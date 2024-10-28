#include <iostream>
#include <vector>

using namespace std;

void solution(int M, vector<vector<int>> &matrix);

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int N, M;
    cin >> N >> M;
    vector<vector<int>> matrix(N + 1, vector<int>(N + 1, 0));
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> matrix[i][j];

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            matrix[i][j] += matrix[i - 1][j] + matrix[i][j - 1] - matrix[i - 1][j - 1];

    solution(M, matrix);
    return 0;
}

void solution(int M, vector<vector<int>> &matrix)
{
    for (int m = 0; m < M; m++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << matrix[x2][y2] - matrix[x1 - 1][y2] - matrix[x2][y1 - 1] + matrix[x1 - 1][y1 - 1] << "\n";
    }
}