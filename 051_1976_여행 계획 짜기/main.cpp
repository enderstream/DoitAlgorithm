#include <iostream>
#include <vector>

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

bool solution(int N, int M);
int find_head(vector<int> &cities, int e);

int main(int argc, char const *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, M;
    cin >> N >> M;

    solution(N, M) ? cout << "YES" : cout << "NO";

    return 0;
}

bool solution(int N, int M)
{
    vector<int> cities(N + 1);
    for (int i = 0; i <= N; i++)
        cities[i] = i;

    vector<vector<int>> connection(N + 1, vector<int>(N + 1, 0));
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> connection[i][j];

    for (int i = 1; i <= N; i++)
        for (int j = i; j <= N; j++)
            if (i == j)
                continue;
            else if (connection[i][j] == 1)
            {
                int head_i = find_head(cities, i);
                int head_j = find_head(cities, j);
                int new_head = min(head_i, head_j);
                cities[head_i] = new_head;
                cities[head_j] = new_head;
            }

    int start, head;
    cin >> start;
    head = find_head(cities, start);

    for (int i = 1; i < M; i++)
    {
        int city;
        cin >> city;
        if (head != find_head(cities, city))
            return false;
    }
    return true;
}

int find_head(vector<int> &cities, int e)
{
    // 내가 루트라면 즉시 리턴
    if (cities[e] == e)
        return e;
        
    // 루트 찾기
    int root = e; // e는 보존해두고, 루트를 찾아 타고 올라가기
    while (cities[root] != root)
        root = cities[root];

    // 경로 압축
    while (e != root)
    {
        int parent = cities[e]; // 부모를 일단 따로 저장
        cities[e] = root;       // 내 부모를 루트로 변경
        e = parent;             // 나를 부모로 교체해서 다음 루프에서 부모의 부모를 다시 루트로 변경
    }
    return root;
}