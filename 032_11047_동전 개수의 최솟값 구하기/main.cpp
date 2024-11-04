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

void solution(int N, int K, vector<int> &coins);

int main(int argc, char const *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, K;
    cin >> N >> K;

    vector<int> coins(N, 0);
    for (int i = N - 1; i >= 0; i--)
        cin >> coins[i];

    solution(N, K, coins);
    return 0;
}

void solution(int N, int K, vector<int> &coins)
{
    int total_coins = 0;
    for (int coin : coins)
    {
        if (coin <= K)
        {
            total_coins += K/coin;
            K %= coin;
        }
        if(!K)
            break;
    }
    cout <<  total_coins;
}