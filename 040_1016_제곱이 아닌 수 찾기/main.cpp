#include <iostream>
#include <vector>
#include <cmath>

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

typedef unsigned long long i64;

void solution(i64 min, i64 max);
vector<i64> sieve_of_eratosthenes(i64 max);

int main(int argc, const char *argv[])
{
    FAST_IO;
    if constexpr (local)
    {
        (void)!freopen("./input.txt", "r", stdin);
        debug << "\n";
    }

    i64 min, max;
    cin >> min >> max;

    solution(min, max);
    return 0;
}

void solution(i64 min, i64 max)
{
    i64 cnt = 0;
    // 루트 max까지로 제한 안하면 밑에서 8테라짜리 벡터가 나옴
    vector<i64> prime_square = sieve_of_eratosthenes(1 + i64(sqrt(max)));
    vector<i64> square_nono;
    for (i64 i = min; i <= max; i++)
        square_nono.push_back(i);

    for (i64 ps : prime_square)
        for (i64 i = (ps - min % ps) % ps; i < square_nono.size(); i += ps)
            square_nono[i] = 0;

    for (i64 sq : square_nono)
        if (sq != 0)
            cnt++;

    cout << cnt;
    /*
     4 9 25 49 121 169 289 361 ...
     101 ~ 1000
     101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 ...
     0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  ...

     101 % 4 == 1 >> (4 - 1) == 3 : 104
     101 & 9 == 2 >> (9 - 2) == 7 : 108
    */
}

vector<i64> sieve_of_eratosthenes(i64 max)
{
    // 이 시점에서 max는 int 범위 내에 들어감
    vector<i64> prime_square = {4};
    vector<bool> is_prime(max, true);
    is_prime[0] = false;
    is_prime[1] = false;

    for (i64 p = 2; p * p <= max; p++)
        if (is_prime[p])
            for (i64 i = p * p; i <= max; i += p)
                is_prime[i] = false;

    for (i64 i = 3; i <= max; i += 2)
        if (is_prime[i])
            prime_square.push_back(i * i);

    return prime_square;
}

/*
max = 1000
2 3 5 7 11 13 17 19 23 29 31 ...

4 9 25 49 121 169 289 361 ...
1 ~ 1000


21 4748 3648
2 * 10^9
10^12
i64 : 18*10^18

O(N) : 100만회
2^2
3^2
4^2??
5^2
...
8 * 10^12 == 8TB...
bool벡터만으로도 8테라나 잡아먹을수가 있구나...
소수의 제곱만 검사해도 충분하더라~~
*/