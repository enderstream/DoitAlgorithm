#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>

#ifdef BOJ // 백준 채점환경
constexpr bool local = false;
#else // 로컬
constexpr bool local = true;
#endif

#define FAST_IO                       \
    std::ios::sync_with_stdio(false); \
    std::cin.tie(nullptr);            \
    std::cout.tie(nullptr);
#define debug            \
    if constexpr (local) \
    std::cout
#define endl "\n"

using namespace std;

typedef pair<int, int> cable;

struct compare
{
    bool operator()(const cable &a, const cable &b) const
    {
        return a.second > b.second;
    }
};

void solution(int N, vector<vector<int>> &network);

int main(int argc, char const *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int cnt = 1;
    // uom은 없는 키를 조회하면 0을 반환하는 점을 이용
    unordered_map<char, int> alphabet_map;
    for (char c = 'a'; c <= 'z'; c++)
        alphabet_map[c] = cnt++;

    for (char c = 'A'; c <= 'Z'; c++)
        alphabet_map[c] = cnt++;

    // total_using : 기부 안하고 내가 쓸 케이블
    int N, total_using;
    cin >> N;
    string line;
    vector<vector<int>> network(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++)
    {
        cin >> line;
        int j = 0;
        for (const char &c : line)
            network[i][j++] = alphabet_map[c];
    }

    solution(N, network);
    return 0;
}

void solution(int N, vector<vector<int>> &network)
{
    // 전처리 하기 전에, 기부할 수 있는 전체 케이블 길이를 계산
    int donation = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            donation += network[i][j];

    // 네트워크 전처리
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
            if (network[i][j] != 0 && network[j][i] != 0)
                network[i][j] = network[j][i] = min(network[i][j], network[j][i]);
            else if (network[i][j] == 0)
                network[i][j] = network[j][i];
            else if (network[j][i] == 0)
                network[j][i] = network[i][j];
    }

    vector<bool> connected(N, false);
    priority_queue<cable, vector<cable>, compare> PQ;
    PQ.push({0, 0});
    connected[0] = true;

    for (int i = 1; i < N; i++)
        if (network[0][i] != 0)
            PQ.push({i, network[0][i]});

    while (!PQ.empty())
    {
        cable next_cable = PQ.top();
        PQ.pop();
        if (!connected[next_cable.first])
        {
            connected[next_cable.first] = true;
            donation -= next_cable.second;
            for (int i = 0; i < N; i++)
                if (i != next_cable.first && !connected[i] && network[next_cable.first][i] > 0)
                    PQ.push({i, network[next_cable.first][i]});
        }
    }

    for (const bool &PC : connected)
        if (!PC)
        {
            donation = -1;
            break;
        }

    cout << donation;
}