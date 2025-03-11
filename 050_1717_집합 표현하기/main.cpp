#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

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

void solution(int n, int m);
void unionise(vector<int> &sets, int a, int b);
bool intersection_check(vector<int> &sets, int a, int b);
int get_head_set(vector<int> &sets, int set);
 
int main(int argc, char const *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    solution(n, m);
    return 0;
}

void solution(int n, int m)
{
    vector<int> sets(n + 1, 0);
    for (int i = 1; i <= n; i++)
        sets[i] = i;

    for (int i = 1; i <= m; i++)
    {
        int op, a, b;
        cin >> op >> a >> b;

        if (op == 0)
            unionise(sets, a, b);
        else if (intersection_check(sets, a, b)) // op == 1
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}

void unionise(vector<int> &sets, int a, int b)
{
    int head = min(get_head_set(sets, a), get_head_set(sets, b));
    sets[a] = head;
    sets[b] = head;
}

bool intersection_check(vector<int> &sets, int a, int b)
{
    return get_head_set(sets, a) == get_head_set(sets, b);
}

int get_head_set(vector<int> &sets, int set)
{
    return 0;
    // if (set == sets[set]) // 내가 대표셋이라면
    //     return set;

    // // 아니라면 대표셋 찾아
    // stack<int> S;
    // while (set != sets[set])
    // {
    //     S.push(set);
    //     set = sets[set];
    // }

    // // 전부 대표셋으로 업데이트
    // while (!S.empty())
    // {
    //     sets[S.top()] = set;
    //     S.pop();
    // }

    // return set;
}