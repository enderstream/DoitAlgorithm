#include <iostream>
#include <unordered_set>

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

void solution(int M, unordered_set<string> &string_set);

int main(int argc, char const *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, M;
    cin >> N >> M;
    string s;
    unordered_set<string> string_set;
    for (int i = 0; i < N; i++)
    {
        cin >> s;
        string_set.insert(s);
    }

    solution(M, string_set);
    return 0;
}

void solution(int M, unordered_set<string> &string_set)
{
    string s;
    int cnt = 0;
    for (int i = 0; i < M; i++)
    {
        cin >> s;
        if (string_set.find(s) != string_set.end())
            cnt++;
    }
    cout << cnt;
}